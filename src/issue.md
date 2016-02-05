# 更新循环

- 场景更新

- 事件更新
- 物理状态更新 / 碰撞检测分块 / 事件(生存状态)更新
- 渲染

## 碰撞组

- 玩家的子弹       :: P[layer]B[ullet]
- 玩家的消弹技能   :: P[layer]S[pell]
- 敌人的子弹       :: E[nemy]B[ullet]
- 玩家机体         :: P[layer]E[ntity]
- 敌人机体         :: E[nemy]E[ntity]
- 道具             :: B[onus]I[tem]
- 不参与碰撞监测   :: GH[ost]

### 数量相对较少 可以被标记到grid的组

- PB
- PS
- PE
- EE

### 会发生碰撞的对

  实体     被   实体       碰撞

- PS @     /    {}
- PB @     /    {}
- EB       /    { PS }
- EE @     /    { PB, PS }
- PE @     /    { EE, EB }
- BI       /    { PE }

  实体    碰撞    实体

-          /       PS
-          /       PB
- PS       /       EB, EE
- PB       /       EE
- PE       /       BI
- EB       /       PE

## 合并的结果

更新顺序 以及更新循环中需要进行的碰撞检测

- PS
- PB
- EE { PB, PS }
- EB { PS     }
- PE { EE, EB }
- BI { PE     }

