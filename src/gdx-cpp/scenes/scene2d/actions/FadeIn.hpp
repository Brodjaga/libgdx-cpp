
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#ifndef GDX_CPP_SCENES_SCENE2D_ACTIONS_FADEIN_HPP_
#define GDX_CPP_SCENES_SCENE2D_ACTIONS_FADEIN_HPP_

#include "gdx-cpp/scenes/scene2d/AnimationAction.hpp"
#include "ActionResetingPool.hpp"

namespace gdx {
namespace scenes {
namespace scene2d {
namespace actions {

class FadeIn: public AnimationAction {
public:
    static FadeIn* build (float duration);
    
    void setTarget (gdx::Actor* actor);
    void act (float delta);
    void finish ();
    Action* copy ();

    FadeIn();

protected:       
    float startAlpha;
    float deltaAlpha;
    Actor* target;

    static ActionResetingPool<FadeIn> pool;
};

} // namespace gdx
} // namespace scenes
} // namespace scene2d
} // namespace actions

#endif // GDX_CPP_SCENES_SCENE2D_ACTIONS_FADEIN_HPP_
