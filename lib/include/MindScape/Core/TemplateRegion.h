#pragma once

#include <MindScape/Utils/DllUtils.h>

#include <GameBackbone/Core/GameRegion.h>


namespace MindScape
{
    class libMindScape TemplateRegion : public GB::GameRegion
    {
    public:
        using GB::GameRegion::GameRegion;
    };
}