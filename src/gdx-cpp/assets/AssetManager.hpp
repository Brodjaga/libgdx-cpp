
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

#ifndef GDX_CPP_ASSETS_ASSETMANAGER_HPP_
#define GDX_CPP_ASSETS_ASSETMANAGER_HPP_

#include "gdx-cpp/utils/Disposable.hpp"
#include "gdx-cpp/utils/Synchronized.hpp"
#include "gdx-cpp/implementation/MutexFactory.hpp"
#include "gdx-cpp/implementation/Thread.hpp"
#include "gdx-cpp/Application.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "Asset.hpp"
#include "AssetLoaderParameters.hpp"
#include "loaders/AssetLoader.hpp"
#include "AssetDescriptor.hpp"
#include "gdx-cpp/assets/AssetType.hpp"
#include "gdx-cpp/internal/unordered_map"

#include <string>
#include <list>
#include <cassert>

namespace gdx {

class Logger;

class AssetLoadingTask;
class AssetErrorListener;
class AssetErrorListener;
class AssetDescriptor;

class AssetManager: public Disposable
            , public Synchronizable
{
    typedef ref_ptr_maker<AssetDescriptor>::shared_ptr_t AssetDescriptorPtr;
    typedef gdx_unordered_map<std::string, Asset::ptr> AssetMap;
    typedef std::list< AssetDescriptorPtr > PreloadQueueType;
    typedef gdx_unordered_map<std::string, int> AssetTypeMap;

public:
    AssetManager();

    Thread::ptr newThread (const Runnable& r);
    void remove (const std::string& fileName);
    bool isLoaded (const std::string& fileName);
    bool update ();
    int getLoadedAssets ();
    int getQueuedAssets ();
    float getProgress ();
    void setErrorListener (const AssetErrorListener& listener);
    void dispose ();
    void clear ();
    Logger& getLogger ();
    std::string& getDiagonistics ();

    template <typename T>
    T& get (const std::string& filename, int type) {
        Synchronizable::lock_holder hnd(synchronize());

        if (assets.count(type) == 0) {
            gdx_log_error("AssetManager.hpp", "Asset '%s' not loaded", filename.c_str());
        }

        const AssetMap& assetsByType = assets[type];
        assert(assetsByType.count(filename));

//         assetsByType[filename];
//         T& asset = (T&) *();
//         return asset;
    }

    bool getAssetFileName (const Asset& asset, std::string& result) ;
    void preload (const std::string& fileName, const AssetType& type, AssetLoaderParameters::ptr parameter) ;
    void preload (const std::string& fileName, const AssetType& type) ;
    void setLoader (AssetType& type, AssetLoader* loader) ;

protected:

    //std::tr1::unordered_map<AssetType, AssetLoader* > loaders;
    gdx_unordered_map<int, AssetMap > assets;

    AssetTypeMap assetTypes;
    gdx_unordered_map<std::string, std::vector<std::string> > assetDependencies;
    PreloadQueueType preloadQueue;
    std::list<AssetLoadingTask*> tasks;

    AssetErrorListener* errorListener;

    int toLoad;
    int loaded;

    void injectDependency (const std::string& parentAssetFilename, AssetDescriptorPtr dependendAssetDesc);
private:
    void nextTask ();
    void addTask (const AssetDescriptor& assetDesc);
    bool updateTask ();
    void incrementRefCountedDependencies (const std::string& parent);
    //void handleTaskError (const Throwable& t);
};

} // namespace gdx

#endif // GDX_CPP_ASSETS_ASSETMANAGER_HPP_
