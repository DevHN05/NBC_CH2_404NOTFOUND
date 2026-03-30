#include "SoundManager.h"

void SoundManager::RegisterSound(SoundType type, const wstring& fileName)
{
    soundTable[type] = fileName;
}

bool SoundManager::PlayBGM(SoundType type)
{
    auto it = soundTable.find(type);
    if (it == soundTable.end())
    {
        return false;
    }

    return PlaySoundW(it->second.c_str(), nullptr, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

bool SoundManager::PlaySFX(SoundType type)
{
    auto it = soundTable.find(type);
    if (it == soundTable.end())
    {
        return false;
    }

    return PlaySoundW(it->second.c_str(), nullptr, SND_FILENAME | SND_ASYNC);
}

void SoundManager::Stop()
{
    PlaySoundW(nullptr, nullptr, 0);
}
void SoundManager::SetBGMVolume(int volume)
{
    bgmVolume = volume;
}
void SoundManager::SetSFXVolume(int volume)
{
    sfxVolume = volume;
}
