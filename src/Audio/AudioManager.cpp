#include "AudioManager.h"
#include "DxLib.h"

AudioManager& AudioManager::Instance()
{
	static AudioManager instance;
	return instance;
}

bool AudioManager::LoadBgm(const std::string& name, const std::string& path)
{
    int h = LoadSoundMem(path.c_str()); // ファイルをメモリに読み込む
    if (h == -1) return false;
    m_bgm[name] = h;
    return true;
}

bool AudioManager::LoadSe(const std::string& name, const std::string& path)
{
    int h = LoadSoundMem(path.c_str()); // ファイルをメモリに読み込む
    if (h == -1) return false;
    m_se[name] = h;
    return true;
}

void AudioManager::PlayBgm(const std::string& name)
{
    if (!m_bgm.count(name)) return; // 指定したBGMが存在しない場合はreturn

    int h = m_bgm[name]; // サウンドハンドルを取得
    if (m_currentBgm == h) return; // すでに同じBGMが再生されている場合はreturn
    ChangeVolumeSoundMem(m_bgmVolume, h);

    StopBgm(); // 現在のBGMを停止

    PlaySoundMem(h, DX_PLAYTYPE_LOOP); // BGMをループ再生
    m_currentBgm = h; // 現在のBGMを更新
}

void AudioManager::StopBgm()
{
    // 現在のBGMが再生されている場合は停止
    if (m_currentBgm != -1)
        StopSoundMem(m_currentBgm);
    m_currentBgm = -1;
}

void AudioManager::PlaySe(const std::string& name)
{
    if (!m_se.count(name)) return; // 指定したSEが存在しない場合はreturn
    ChangeVolumeSoundMem(m_bgmVolume, m_se[name]);
    PlaySoundMem(m_se[name], DX_PLAYTYPE_BACK); // SEは重ねて再生
}