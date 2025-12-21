#include "Public/Gameplay/Crop/CropVisualData.h"

const FCropStageVisual* UCropVisualData::GetVisual( ECropGrowthStage Stage ) const
{
    return StageVisuals.Find( Stage );
}
