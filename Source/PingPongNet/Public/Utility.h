#pragma once

class UWorld;
class APlayerController;
class AController;

#define LOG(s, ...)         UE_LOG(LogTemp, Log,        TEXT(s), ##__VA_ARGS__)
#define WARNING(s, ...)     UE_LOG(LogTemp, Warning,    TEXT(s), ##__VA_ARGS__)
#define ERROR(s, ...)       UE_LOG(LogTemp, Error,      TEXT(s), ##__VA_ARGS__)

#define SCREEN_LOG(s)       { if(GEngine) {GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, s); }}
#define SCREEN_WARNING(s)   { if(GEngine) {GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, s); }}
#define SCREEN_ERROR(s)     { if(GEngine) {GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, s); }}

#define GetValidWorld \
[this]() -> UWorld*                        \
{                                          \
    UWorld* World = GetWorld();            \
    if (!IsValid(World))                   \
    {                                      \
        ERROR("World is invalid, wow!");   \
        return nullptr;                    \
    }                                      \
    return World;                          \
}

