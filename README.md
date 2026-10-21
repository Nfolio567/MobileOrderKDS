# Json example

```json
{"orders":
  [
    {
      "id":"27A22E",
      "isCooking":false,
      "isCooked":false,
      "isProvided":false,
      "items":[
        {
          "product":"焼きそば（ソース）",
          "options":[],
          "quantity":1
        },
        {
          "product":"焼きそば（ソース）",
          "options":["きざみネギ"],
          "quantity":3
        }
      ]
    }
  ]
}
```

# 注文状態のイロハ
🔴<span style="color: red;">調理前</span>\
🟡<span style="color: yellow;">調理中</span>\
🟢<span style="color: lightgreen;">提供前</span>
