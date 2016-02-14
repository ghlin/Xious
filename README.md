# Xious

STG Library

施工中 🚧  ...



## 基本想法

以组合的方式描述实体的活动。

预计可能的例子🌰 :

``` c++

auto action = compose(
  schedule(REPEAT_INF,
           { stay(), stay_time_out },
           { move(M_PI / 3, curve::Cubic, duration, change_value), mov_time_out }),
  move(0, curve::Sin, duration, change_value),
  move(M_PI / 2, curve::Cos, duration, change_value),
  schedule(REPEAT_INF,
          { stay(), sleep_time_out },
          { shoot(bullet_actor, interval), shoot_time_out }));

enemy->set_action(action);

```

