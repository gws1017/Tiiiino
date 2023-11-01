// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuUI/RankWidget.h"
#include "Components/CanvasPanelSlot.h"
void URankWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

TArray<float>& URankWidget::GetCharacterDistanceData()
{
	CharacterDistanceData.Empty();

	for (auto& data : RankData)
	{
		CharacterDistanceData.Add(data.first);
	}

	return CharacterDistanceData;
}

void URankWidget::CalculateNewRank()
{
	auto network = Network::GetNetwork();
	std::sort(RankData.begin(), RankData.end(), [](const auto& lhs, const auto& rhs) {
		return lhs.first > rhs.first;
		});

	int cnt = 1;

	for (auto& data : RankData)
	{
		if (data.second == network->mMyCharacter)
		{
			sCurrentRank = cnt;
			break;
		}
		cnt++;
	}

}

void URankWidget::GetDataOfCharacters()
{

	if (!bIsLevelLoaded) {
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGoalArea::StaticClass(), FoundActors);
		CLog::Log("Found Actors...");
		if (FoundActors.IsEmpty()) {
			return;
		}

		if (FoundActors.Num() > 1) {
			return;
		}

		EndPosition = FoundActors[0]->GetActorLocation();
		fTrackDistance = EndPosition.Y - StartPosition.Y;
		bIsLevelLoaded = true;
	}


	// 10/28 ������
	// ������ �ڷᱸ�� ������ ������ ���� �ʱ� ������
	// ���߿� ������ ����
	// ��ġ�� 8�� �ۿ� ���µ� �� �����Ƶ� ���� ������...
	auto network = Network::GetNetwork();

	// �� �༮�� ������ �ű�� ���� �༮�̱� ������ �Ź� Ŭ���� ���ش�.
	RankData.clear();

	for (int i = 0; i < 8; ++i)
	{
		if (network->mOtherCharacter[i] == nullptr) {
			continue;
		}
		ATinoCharacter* curCharacter = network->mOtherCharacter[i];

		// ���� ������ ������ �� �Ÿ��� ������ ������� �����ߴ��� ���´�.
		// ���� ������ ������ ���� ���� - ��ŸƮ ���� �ϸ� �ȴ�.
		float DistanceData = (curCharacter->GetActorLocation().Y - StartPosition.Y) / fTrackDistance;

		if (DistanceData < 0.f) {
			DistanceData = 0.f;
		}

		if (DistanceData > 1.f) {
			DistanceData = 1.f;
		}

		auto findIt = PtrBasedRankData.find(curCharacter);

		// Map ���ο� �̹� �� �ֳ�?
		if (findIt == PtrBasedRankData.end()) {
			// Map ���ο� ������ �߰��� ��� �Ѵ�
			PtrBasedRankData.insert(std::make_pair(curCharacter, DistanceData));
		}
		else {
			// Map ���ο� ������ ���� ������ �ָ� �ȴ�.
			(*findIt).second = DistanceData;
		}
		
		RankData.emplace_back(std::make_pair(DistanceData, curCharacter));
		OtherCharacterDistanceData.Add(DistanceData);
	}

	if (network->mMyCharacter != nullptr) {
		ATinoCharacter* curCharacter = network->mMyCharacter;

		float DistanceData = (curCharacter->GetActorLocation().Y - StartPosition.Y) / fTrackDistance;

		if (DistanceData < 0.f) {
			DistanceData = 0.f;
		}

		if (DistanceData > 1.f) {
			DistanceData = 1.f;
		}

		auto findIt = PtrBasedRankData.find(curCharacter);

		// Map ���ο� �̹� �� �ֳ�?
		if (findIt == PtrBasedRankData.end()) {
			// Map ���ο� ������ �߰��� ��� �Ѵ�
			PtrBasedRankData.insert(std::make_pair(curCharacter, DistanceData));
		}
		else {
			// Map ���ο� ������ ���� ������ �ָ� �ȴ�.
			(*findIt).second = DistanceData;
		}

		RankData.emplace_back(std::make_pair(DistanceData, curCharacter));
		myCharcaterDistanceData = DistanceData;
	}
	else {
		myCharcaterDistanceData = -1.0f;
	}
}

void URankWidget::ChangePositionByDistanceData()
{
	std::vector<UImage*> images;
	
	images.push_back(OtherCharacterImage0);
	images.push_back(OtherCharacterImage1);
	images.push_back(OtherCharacterImage2);
	images.push_back(OtherCharacterImage3);
	images.push_back(OtherCharacterImage4);
	images.push_back(OtherCharacterImage5);
	images.push_back(OtherCharacterImage6);

	TArray<float> distanceData = GetCharacterDistanceData();

	for (int i = 0; i < distanceData.Num(); ++i)
	{
		if (i == sCurrentRank - 1 ) continue;
		UCanvasPanelSlot* canvasPanel = UWidgetLayoutLibrary::SlotAsCanvasSlot(images[i]);
		canvasPanel->SetPosition(FVector2D(1280.f * distanceData[i], 0.0f));
	}
	UCanvasPanelSlot* canvasPanel = UWidgetLayoutLibrary::SlotAsCanvasSlot(MyCharacterImage);
	canvasPanel->SetPosition(FVector2D(1280.f * distanceData[sCurrentRank - 1], 0.0f));
	



}

void URankWidget::NativeTick(const FGeometry& Geometry, float InDeltaTime)
{
	Super::NativeTick(Geometry, InDeltaTime);

	// ĳ���� ������ ������
	GetDataOfCharacters();

	// ���� ��ũ ��������
	CalculateNewRank();

	// ��ũ �����͸� �������� ��ġ �ٲ��ֱ�
	ChangePositionByDistanceData();
}
