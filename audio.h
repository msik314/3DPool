#ifndef AUDIO_H
#define AUDIO_H

#ifdef _WIN32
#include <windows.h>
#include <Mmsystem.h>
#endif // _WIN32
inline void playSound(const char* sound)
{
    #ifdef _WIN32
    PlaySound(sound, NULL, SND_FILENAME | SND_ASYNC);
    #endif // _WIN32
}

inline void stopSounds()
{
    #ifdef _WIN32
    PlaySound(NULL, NULL, 0);
    #endif // _WIN32
}

#endif // AUDIO_H
