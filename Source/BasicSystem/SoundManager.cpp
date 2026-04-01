#include "SoundManager.h"

namespace
{
    void ApplyWaveOutVolume(int volume)
    {
        const int clamped = (volume < 0) ? 0 : (volume > 100 ? 100 : volume);
        const DWORD waveVolume = static_cast<DWORD>((0xFFFF * clamped) / 100);
        const DWORD stereoVolume = (waveVolume & 0xFFFF) | (waveVolume << 16);
        waveOutSetVolume(nullptr, stereoVolume);
    }
}

int SoundManager::ClampVolume(int volume)
{
    if (volume < 0) return 0;
    if (volume > 100) return 100;
    return volume;
}

bool SoundManager::SendMciCommand(const wstring& command)
{
    return mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
}

bool SoundManager::GetMciStatus(const wstring& alias, const wstring& item, wstring& outValue)
{
    wchar_t buffer[128] = {};
    wstring command = L"status " + alias + L" " + item;
    if (mciSendStringW(command.c_str(), buffer, 128, nullptr) != 0)
    {
        return false;
    }

    outValue = buffer;
    return true;
}

void SoundManager::CleanupFinishedSFX()
{
    vector<wstring> stillActive;

    for (const wstring& alias : activeSfxAliases)
    {
        wstring mode;
        if (GetMciStatus(alias, L"mode", mode) && mode == L"playing")
        {
            stillActive.push_back(alias);
            continue;
        }

        SendMciCommand(L"stop " + alias);
        SendMciCommand(L"close " + alias);
    }

    activeSfxAliases = stillActive;
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

    CleanupFinishedSFX();

    const wstring alias = L"sfx" + to_wstring(++sfxAliasCounter);

    if (!SendMciCommand(L"open \"" + it->second + L"\" type waveaudio alias " + alias))
    {
        return false;
    }

    const int mciVolume = ClampVolume(sfxVolume) * 10;
    SendMciCommand(L"setaudio " + alias + L" volume to " + to_wstring(mciVolume));

    if (!SendMciCommand(L"play " + alias))
    {
        SendMciCommand(L"close " + alias);
        return false;
    }

    activeSfxAliases.push_back(alias);
    return true;
}

void SoundManager::Stop()
{
    PlaySoundW(nullptr, nullptr, 0);

    for (const wstring& alias : activeSfxAliases)
    {
        SendMciCommand(L"stop " + alias);
        SendMciCommand(L"close " + alias);
    }

    activeSfxAliases.clear();
}

void SoundManager::SetBGMVolume(int volume)
{
    bgmVolume = ClampVolume(volume);
    ApplyWaveOutVolume(bgmVolume);
}

void SoundManager::SetSFXVolume(int volume)
{
    sfxVolume = ClampVolume(volume);
}
