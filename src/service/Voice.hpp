#pragma once

#include <QSoundEffect>
#include <queue>

class MyVoice : public QObject {
  Q_OBJECT

public:
  explicit MyVoice(QObject *parent = nullptr);

  Q_INVOKABLE void playOrderVoice(const QString &message);

private:
  void playNext();

  enum VoiceLabel : std::uint8_t {
    FirstVoice,
    LastVoice,
    TenVoice,
    HundredVoice,
  };

  std::vector<QSoundEffect*> m_sounds;
  std::queue<QSoundEffect*> m_queue;
  QSoundEffect* m_current = nullptr;
  QUrl m_voiceRoot = QUrl("qrc:/qt/qml/QMLModules/resources/voices/");
  const int ALPHABET_CONVERT_NUM = 53;
  const int NUMBER_CONVERT_NUM = 3;

  const int SOUND_QUANTITY = 38;
};
