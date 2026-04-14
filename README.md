# 내일배움캠프 Unreal Engine 5 부트캠프
## Chapter 2 팀 프로젝트
### 팀
404 NOT FOUND (4조)
### 팀원
- **한승재** (Game System, Character System, Dice System 구현)
- 김시리 (Monster, Boss Monster, Shop System 구현)
- 김유민 (Logger System 구현)
- 오성현 (Item System 구현)
- 장진희 (Game System, Graphic System, Combat System 구현)
- 최민서 (Event System, Boss Monster 구현)
## 게임 이름
404 NOT FOUND
## 게임 특징
- 플레이어의 기본적인 RPG 요소
  - 체력, 스탯, 치명타 등
- TRPG의 주사위 굴리기 요소 차용
  - 이벤트마다 다른 주사위 요구치
  - 캐릭터의 스탯, 소지하고 있는 아이템에 따라 추가되는 보너스 판정값
  - 1이 나오면 대실패, 주사위의 최댓값이 나오면 대성공
- 깔끔한 ASCII 그래픽
  - 정보별로 분리되어 보기 편한 UI
- 선형적이지만 플레이어의 선택에 따라 달라지는 이벤트
  - 확률에 따라 만날 수 있는 몬스터와의 전투, 상점, 특별 이벤트
## 파일 구조
- `NBC_CH2_404NOTFOUND.cpp` → 게임 실행
- `GameSystem.cpp` → 게임 내 기본 구조 구현
- `DiceSystem.cpp` → 주사위 시스템 구현
- `CombatManager.cpp` → 전투 시스템 구현
- `GraphicManager.cpp` → 기본 UI, Console 출력 구현
- `BaseCharacter.cpp` → 기본 캐릭터 구현
  - `PlayerManager.cpp` → 플레이어 구현
  - `BaseMonster.cpp` → 몬스터 구현
    - `BaseBossMonster.cpp` → 보스 몬스터 구현
    - `MonsterData.h` → 몬스터 정보 저장
- `ItemManager.cpp` → 아이템 구현
  - `Inventory.cpp` → 인벤토리 구현
  - `Equipment.cpp` → 장착 아이템 구현
  - `Potion.cpp` → 사용 아이템 구현
- `ShopManager.cpp` → 상점 시스템 구현
- `LoggerSystem.cpp` → 게임의 출력 시스템 구현
