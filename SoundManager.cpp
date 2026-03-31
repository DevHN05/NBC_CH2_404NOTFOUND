#include "SoundManager.h"

namespace
{
    int ClampVolume(int volume)
    {
        if (volume < 0)
        {
            return 0;
        }

        if (volume > 100)
        {
            return 100;
        }

        return volume;
    }

    void ApplyWaveOutVolume(int volume)
    {
        const int clamped = ClampVolume(volume);
        const DWORD waveVolume = static_cast<DWORD>((0xFFFF * clamped) / 100);
        const DWORD stereoVolume = (waveVolume & 0xFFFF) | (waveVolume << 16);
        waveOutSetVolume(nullptr, stereoVolume);
    }
}

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

    ApplyWaveOutVolume(bgmVolume);
    return PlaySoundW(it->second.c_str(), nullptr, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

bool SoundManager::PlaySFX(SoundType type)
{
    auto it = soundTable.find(type);
    if (it == soundTable.end())
    {
        return false;
    }

    ApplyWaveOutVolume(sfxVolume);
    return PlaySoundW(it->second.c_str(), nullptr, SND_FILENAME | SND_ASYNC);
}

void SoundManager::Stop()
{
    PlaySoundW(nullptr, nullptr, 0);
}
void SoundManager::SetBGMVolume(int volume)
{
    bgmVolume = ClampVolume(volume);
    ApplyWaveOutVolume(bgmVolume);
}
void SoundManager::SetSFXVolume(int volume)
{
    sfxVolume = ClampVolume(volume);
    ApplyWaveOutVolume(sfxVolume);
}
