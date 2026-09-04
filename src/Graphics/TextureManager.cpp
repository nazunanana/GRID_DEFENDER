#include "TextureManager.h"
#include "DxLib.h"

TextureManager& TextureManager::Instance()
{
    static TextureManager instance;
    return instance;
}

void TextureManager::Load()
{
    // ウィルス
    for (int i = 0; i < static_cast<int>(ColorId::COUNT); ++i)
        m_virusGraph[i] = -1;
    m_virusGraph[static_cast<int>(ColorId::Magenta)] = LoadGraph("img/magenta_virus.png");
    m_virusGraph[static_cast<int>(ColorId::Cyan)]    = LoadGraph("img/cyan_virus.png");
    m_virusGraph[static_cast<int>(ColorId::Purple)]  = LoadGraph("img/purple_virus.png");
    m_coreGraph = LoadGraph("img/core_tex.png");
    m_fieldGraph = LoadGraph("img/field_tex3.png");
    m_hpGraph = LoadGraph("img/hp_tex.png");
}

void TextureManager::Unload()
{
    for (int i = 0; i < static_cast<int>(ColorId::COUNT); ++i)
    {
        if (m_virusGraph[i] != -1)
        {
            DeleteGraph(m_virusGraph[i]);
            m_virusGraph[i] = -1;
        }
    }
    if (m_coreGraph  != -1) {
        DeleteGraph(m_coreGraph);
        m_coreGraph  = -1;
    }
    if (m_fieldGraph != -1) {
        DeleteGraph(m_fieldGraph);
        m_fieldGraph = -1;
    }
    if (m_hpGraph    != -1) {
        DeleteGraph(m_hpGraph);
        m_hpGraph    = -1;
    }
}

int TextureManager::GetVirusGraph(ColorId color) const
{
    const int index = static_cast<int>(color);
    if (index < 0 || index >= static_cast<int>(ColorId::COUNT)) return -1;
    return m_virusGraph[index];
}