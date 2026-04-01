#pragma once
#pragma comment(lib, "winmm.lib")
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include <unordered_map>
using namespace std;

enum class SoundType
{
    TitleBGM,
    BattleBGM,
    ChooseBGM,
    TutorialBGM,
    AttackSFX,
    DiceSFX,
    DiceWinSFX,
    DiceLoseSFX,
    GoldSFX,
    KilkilSFX,
    BossBattleBGM
};

class SoundManager
{
public:
    static SoundManager& GetInstance()
    {
        static SoundManager instance;
        return instance;
    }
    SoundManager(const SoundManager&) = delete;
    void operator=(const SoundManager&) = delete;

    void RegisterSound(SoundType type, const wstring& fileName);
    bool PlayBGM(SoundType type);
    bool PlaySFX(SoundType type);
    void Stop();

    void SetBGMVolume(int volume);
    void SetSFXVolume(int volume);

private:
    SoundManager() = default;

    unordered_map<SoundType, wstring> soundTable;
    int bgmVolume = 50;
    int sfxVolume = 50;

    int sfxAliasCounter = 0;
    vector<wstring> activeSfxAliases;

    int ClampVolume(int volume);
    bool SendMciCommand(const wstring& command);
    bool GetMciStatus(const wstring& alias, const wstring& item, wstring& outValue);
    void CleanupFinishedSFX();
};
