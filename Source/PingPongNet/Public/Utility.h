#pragma once

#include <format>

class UWorld;
class APlayerController;
class AController;

#define LOG(s, ...)     UE_LOG(LogTemp, Log,     TEXT(s), ##__VA_ARGS__)
#define WARNING(s, ...) UE_LOG(LogTemp, Warning, TEXT(s), ##__VA_ARGS__)
#define ERROR(s, ...)   UE_LOG(LogTemp, Error,   TEXT(s), ##__VA_ARGS__)

#define LOG_FROM_SCREEN(s, ...)     UE_LOG(LogTemp, Log,     s, ##__VA_ARGS__)
#define WARNING_FROM_SCREEN(s, ...) UE_LOG(LogTemp, Warning, s, ##__VA_ARGS__)
#define ERROR_FROM_SCREEN(s, ...)   UE_LOG(LogTemp, Error,   s, ##__VA_ARGS__)

#define MY_SCREEN_MESSAGE(log_macros, color, s, ...)                        \
{   const auto msg = std::format(s, ##__VA_ARGS__);                         \
    if(GEngine)                                                             \
    {                                                                       \
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, (color), msg.c_str());  \
    }                                                                       \
    log_macros(TEXT("%s"), StringCast<TCHAR>(msg.c_str()).Get());           \
}
#define SCREEN_LOG(s, ...)       MY_SCREEN_MESSAGE(LOG_FROM_SCREEN, FColor::Green, s, ##__VA_ARGS__)
#define SCREEN_WARNING(s, ...)   MY_SCREEN_MESSAGE(WARNING_FROM_SCREEN, FColor::Yellow, s, ##__VA_ARGS__)
#define SCREEN_ERROR(s, ...)     MY_SCREEN_MESSAGE(ERROR_FROM_SCREEN, FColor::Red, s, ##__VA_ARGS__)

#define GET_VALID_WORLD                           \
[this]() -> UWorld*                               \
{                                                 \
    UWorld* World = GetWorld();                   \
    if (!IsValid(World))                          \
    {                                             \
        SCREEN_ERROR("World is invalid, wow!");   \
        return nullptr;                           \
    }                                             \
    return World;                                 \
}

