#include "Public/Core/Time/FarmTimeSubsystem.h"

void UFarmTimeSubsystem::RegisterDayListener( const TScriptInterface< IDayAdvanceListener >& Listener )
{
    if ( !Listener )
        return;

    DayListeners.AddUnique( Listener );
}

void UFarmTimeSubsystem::UnregisterDayListener( const TScriptInterface< IDayAdvanceListener >& Listener )
{
    DayListeners.Remove( Listener );
}

void UFarmTimeSubsystem::AdvanceDay()
{
    ++CurrentDay;
    UE_LOG( LogTemp, Warning, TEXT("[Time] Advanced to Day %d"), CurrentDay );
    // Blueprint event
    OnDayChanged.Broadcast( CurrentDay );

    // C++ interface listeners
    for ( const auto& Listener : DayListeners )
    {
        if ( !Listener )
            continue;
        Listener->OnDayAdvanced( CurrentDay );
    }
}

int32 UFarmTimeSubsystem::GetCurrentDay() const
{
    return CurrentDay;
}
