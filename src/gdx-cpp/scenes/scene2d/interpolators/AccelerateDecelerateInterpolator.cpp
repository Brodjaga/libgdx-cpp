
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

#include "AccelerateDecelerateInterpolator.hpp"

using namespace gdx::interpolators;

AccelerateDecelerateInterpolator& AccelerateDecelerateInterpolator::newObject () {
    return new AccelerateDecelerateInterpolator();
}

AccelerateDecelerateInterpolator& AccelerateDecelerateInterpolator::$ (float factor) {
    AccelerateDecelerateInterpolator inter = pool.obtain();
    inter.factor = factor;
    inter.doubledFactor = factor * 2;
    return inter;
}

AccelerateDecelerateInterpolator& AccelerateDecelerateInterpolator::$ () {
    return $(DEFAULT_FACTOR);
}

void AccelerateDecelerateInterpolator::finished () {
    pool.free(this);
}

float AccelerateDecelerateInterpolator::getInterpolation (float input) {
    return (float)(Math.cos((input + 1) * Math.PI) / 2.0f) + 0.5f;
}

gdx::Interpolator& AccelerateDecelerateInterpolator::copy () {
    return $(factor);
}

