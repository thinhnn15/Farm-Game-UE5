#include "Public/Core/Time/FarmTimeSubsystem.h"

void UFarmTimeSubsystem::AdvanceDay()
{
    ++m_CurrentDay;
    UE_LOG( LogTemp, Warning, TEXT("[Time] Advanced to Day %d"), m_CurrentDay );
    OnDayChanged.Broadcast( m_CurrentDay );
}

int32 UFarmTimeSubsystem::GetCurrentDay() const
{
    return m_CurrentDay;
}
