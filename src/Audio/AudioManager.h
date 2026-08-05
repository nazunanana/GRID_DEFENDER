#pragma once
#include <string>
#include <unordered_map>

class AudioManager
{
public:
    static AudioManager& Instance();

    // BGMとSEの読み込み
    bool LoadBgm(const std::string& name, const std::string& path);
    bool LoadSe(const std::string& name, const std::string& path);

    // BGMの再生と停止、SEの再生
    void PlayBgm(const std::string& name);
    void StopBgm();
    void PlaySe(const std::string& name);

private:
    // 名前とサウンドハンドルのマップ
    std::unordered_map<std::string, int> m_bgm;
    std::unordered_map<std::string, int> m_se;
    int m_currentBgm = -1;
    int m_bgmVolume = 128;
    int m_seVolume = 128;
};