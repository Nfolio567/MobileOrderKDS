#include "Voice.hpp"

#include <QDebug>

MyVoice::MyVoice(QObject *parent):
  QObject(parent)
{
  // 音声ファイル登録
  QString relativeUrl = "";
  for (int i=0;i<SOUND_QUANTITY;i++) {
    m_sounds.emplace_back(new QSoundEffect(this));
    switch (i) {
      case 0: // '注文番号'
        relativeUrl = "first-voice.wav";
        break;
      case 1: // 'のお客様、カウンターまでお越しください。'
        relativeUrl = "last-voice.wav";
        break;
      case 2: // 'ジュウ'
        relativeUrl = "ten.wav";
        break;
      case 3: // 'ヒャク'
        relativeUrl = "hundred.wav";
        break;
      case 4 ... 11: // 数字の声
        relativeUrl = QString("%1.wav").arg(i - NUMBER_CONVERT_NUM);
        break;
      default: // アルファベットの声
        relativeUrl = QString("%1.wav").arg(QChar(i + ALPHABET_CONVERT_NUM));
        break;
    }
    // 登録
    m_sounds.back()->setSource(m_voiceRoot.resolved(QUrl(relativeUrl)));
  }

  // 自分が再生され終わったら、次のキューに入ってる音声を再生
  for (const auto* sound : m_sounds) {
    connect(
      sound,
      &QSoundEffect::playingChanged,
      this,
      [this, sound]() -> void {
        if (m_current == sound && !sound->isPlaying()) {
          playNext();
        }
      }
    );
  }
}

void MyVoice::playOrderVoice(const QString &message) {
  // まず、キューに最初に流す音声を追加
  m_queue.push(m_sounds[FirstVoice]);

  // ここで一旦数字に変換できるか試す（POSで注文したやつかどうか)
  bool ok = true;
  int orderNum = message.toInt(&ok);

  // できなかった場合(アルファベット混じりの、モバイルオーダー注文番号)
  if (!ok) {
    // 一文字ごとに適応する音声を再生
    for (const QChar &ch : message) {
      if (ch.unicode() >= '1' && '8' >= ch.unicode()) {
        // 数字の場合
        m_queue.push(m_sounds[ch.digitValue() + NUMBER_CONVERT_NUM]);
      } else if (ch.unicode() >= 'A' && 'Z' >= ch.unicode()) {
        // アルファベットの場合
        m_queue.push(m_sounds[ch.unicode() - ALPHABET_CONVERT_NUM]);
      }
    }
  } else { // できた場合(数字だけのPOSで注文したやつ)
    // 桁数なので1始まり
    int count = 1;
    // 割っていって、今の数
    int prevNum = orderNum;
    while (true) {
      // 10で割っていって余りが0になるまで繰り返し
      prevNum /= 10;
      if (prevNum == 0) { // 余りが0
        break;
      }
      // 桁数増やす
      ++count;
    }

    // 一文字ごとに適応する音声を再生(今回は数字だけ)
    for (const QChar &ch : message) {
      const int num = ch.digitValue();
      // 数字が1より上or数字が1だったとしても、1の位のとき
      if (num > 1 || (num == 1 && count == 1)) {
        // 数字の音声をキューに追加
        m_queue.push(m_sounds[ch.digitValue() + NUMBER_CONVERT_NUM]);
      }

      if (num < 1) {
        continue;
      }
      // ~ジュウ、とかの10の位以上で発するやつをキューに追加するかどうか
      QSoundEffect* sound = nullptr;
      if (count == 2) { // 10の位のとき
        sound = m_sounds[TenVoice];
      } else if (count == 3) { // 100のくらいのとき
        sound = m_sounds[HundredVoice];
      }
      // キューに追加
      if (sound != nullptr) {
        m_queue.push(sound);
        // 今の再生する桁数をデクリメント
        --count;
      }
    }
  }

  // 最後に流す音声をキューに追加
  m_queue.push(m_sounds[LastVoice]);

  // そもそも今何も流れてないのならば、再生しちゃう
  if (m_current == nullptr) {
    qDebug() << m_queue.front()->status();
    if (m_queue.front()->status() == QSoundEffect::Ready) {
      playNext();
    } else {
      connect(
        m_queue.front(),
        &QSoundEffect::statusChanged,
        this,
        [this]() -> void {
          if (m_queue.front()->status() == QSoundEffect::Ready) {
            playNext();
          }
        }
      );
    }
  }
}

void MyVoice::playNext() {
  // キューがなくなったら、m_current(今流れてる音声)の中身消す
  if (m_queue.empty()) {
    m_current = nullptr;
    return;
  }
  // キューの最初取得
  m_current = m_queue.front();
  // 再生
  qDebug() << m_current->status();
  m_current->play();
  qDebug() << "play";
  // キューから削除
  m_queue.pop();
}
