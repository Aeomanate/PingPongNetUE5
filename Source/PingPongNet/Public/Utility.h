#pragma once

#include <format>

class UWorld;
class APlayerController;
class AController;

#define LOG_CONSOLE(s, ...)         UE_LOG(LogTemp, Log,        s, ##__VA_ARGS__)
#define WARNING_CONSOLE(s, ...)     UE_LOG(LogTemp, Warning,    s, ##__VA_ARGS__)
#define ERROR_CONSOLE(s, ...)       UE_LOG(LogTemp, Error,      s, ##__VA_ARGS__)

#define MY_SCREEN_MESSAGE(console_macros, color, s, ...)                                             \
{   const auto msg = std::format(s, ##__VA_ARGS__);                                  \
    if(GEngine)                                                                                      \
    {                                                                                                \
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, (color), msg.c_str());                           \
    }                                                                                                \
    console_macros(TEXT("%s"), StringCast<TCHAR>(msg.c_str()).Get());                                \
}
#define SCREEN_LOG(s, ...)       MY_SCREEN_MESSAGE(LOG_CONSOLE, FColor::Green, s, ##__VA_ARGS__)
#define SCREEN_WARNING(s, ...)   MY_SCREEN_MESSAGE(WARNING_CONSOLE, FColor::Yellow, s, ##__VA_ARGS__)
#define SCREEN_ERROR(s, ...)     MY_SCREEN_MESSAGE(ERROR_CONSOLE, FColor::Red, s, ##__VA_ARGS__)

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

