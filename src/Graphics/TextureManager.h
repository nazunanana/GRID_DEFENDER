#pragma once
#include "../GameSystem/Common.h"

class TextureManager
{
public:
    static TextureManager& Instance();

    void Load(); // テクスチャをロード
    void Unload();    // テクスチャをアンロード

    int GetVirusGraph(ColorId color) const;
    int GetCoreGraph()  const { return m_coreGraph; }
    int GetFieldGraph() const { return m_fieldGraph; }
    int GetHpGraph()    const { return m_hpGraph; }

private:
    int m_virusGraph[static_cast<int>(ColorId::COUNT)] = {};
    int m_coreGraph = -1;
    int m_fieldGraph = -1;
    int m_hpGraph = -1;
};