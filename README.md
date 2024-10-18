# Tiiiino

> **Unreal Engine 5, C++**, BP, Jira

### 개발 인원

- (13명) 클라이언트 2명, 서버 3명, 클라 및 서버 1명, 기획 2명, 그래픽 2명, 사운드 1명, PM1명, PD 1명

### 개발 기간

- 2023.09.15 ~ 2023.11.16
  
> 💡 **단기간에 제작**한 프로젝트로, 시간 내에 게임을 완성하기 위해  많은 인원이 참여했습니다.한국공학대학교 홍보 마스코트인 ‘티노’를 활용해 **폴가이즈와 비슷한 형태로 게임**을 제작했습니다.
**기획자나 아트**와 같은 **다양한 직군과 협업**해 보며 **리드 클라이언트를 맡아** 작업 배분이나, 다른 팀원을 지원하는 역할을 수행하며 흔치 않은 경험을 했습니다. 
소규모로 인원을 모집하여 **FGT**(10.13, 8:00 ~ 10:00)를 통해 사용자 **피드백을 수집해 게임을 개선**했고, 이후 좀 더 개발을 거쳐 3일간(11.14 ~11.16) **OBT를 실시**했습니다.

### 구현 내용

---

- **애니메이션 적용 및 조건에 따른 전환** (이동, 점프, 다이빙, 착지(Tumble), 잡기 )
  - AnimGraph 및 Montage 이용
- 장애물 구현
  - 스피드 링(지나치면 N초간 가속)
  - 선형 컨베이어 벨트
  - 선풍기
  - 부숴지는 벽(GeometryColletionComponent 사용)
- 사운드 적용
  - 어디서든 접근이 가능한 **사운드 매니저 액터 클래스**
  - 사운드 매니저 액터를 통해서 배경음악이나 효과음 재생
  - **Attenuation 에셋**을 이용해 거리에 따른 **소리 감쇠 적용**
- **동기화** 서포트
  - 동기화가 필요한 **장애물에서 패킷전송** (서버가 구현한 함수사용)
  - 전달받은 패킷에 따라 **동기화 처리**(플레이어의 애니메이션 패킷을 받으면, 다른 플레이어의 **애니메이션을 재생**함)
  - 다른 플레이어 **위치정보를 받아서 이동 보간을 적용**(서버가 이전 프레임에 보내준 패킷 데이터와 현재 받은 패킷데이터를 비교하여 보간함)
- 악세사리 장착
  - 블루프린트로 생성된 악세사리들을 장착하는 기능 구현

    
### Youtube
[![Youtube Link](http://img.youtube.com/vi/_c1S3dwNWuA/0.jpg)](https://www.youtube.com/watch?v=_c1S3dwNWuA)

### 사진

---

![GIF_2023-11-20_EC98A4ED9B84_2-16-27](https://github.com/user-attachments/assets/f2e3f0ef-e5b8-41c8-a9e9-0c55a10cee57)
![GIF_2023-11-20_EC98A4ED9B84_2-12-03](https://github.com/user-attachments/assets/25f4a666-95a1-4ffc-a9c4-e2fb00cbf4fc)
![GIF_2023-10-14_EC98A4ECA084_12-23-00](https://github.com/user-attachments/assets/4227421e-1f25-45bf-bf77-a41d8696d365)
![GIF_2023-10-14_EC98A4ECA084_12-02-41](https://github.com/user-attachments/assets/754bedff-c488-4ec7-9ac1-d02456b9e4aa)
![GIF_2023-10-10_EC98A4ECA084_1-29-11_(1)](https://github.com/user-attachments/assets/ec6b2eaf-2bff-4d54-9f96-3de19d751e56)
![GIF_2023-10-09_EC98A4ECA084_1-12-41](https://github.com/user-attachments/assets/0eb1d292-6f32-4381-8d3d-d969cd369695)
![GIF_2023-10-01_EC98A4ED9B84_4-57-47](https://github.com/user-attachments/assets/94b81021-8e3a-4544-9b58-fa58c9a9560c)
![GIF_2023-10-01_EC98A4ED9B84_4-53-30](https://github.com/user-attachments/assets/a8d0834a-fb23-4a1e-9164-4f060f148813)
