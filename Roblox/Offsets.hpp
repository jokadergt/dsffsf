#pragma once

#include <cstdint>
#include <memory>
#include <Windows.h>

struct lua_State;
struct YieldState;
struct YieldingLuaThread;

using LuaVMLoad_t = int(__fastcall*)(lua_State* thread, void* bytecode, const char* chunkName, int env);

#define REBASE(Address) (Address + reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr)))

namespace Offsets
{
    const uintptr_t Print = REBASE(0x4C27BF0);
    const uintptr_t OpcodeLookupTable = REBASE(0x639F7B0);
    const uintptr_t ScriptContextResume = REBASE(0x1E21510);
    const uintptr_t GetLuaStateForInstance = REBASE(0x1D56360);
    const uintptr_t LuaVMLoad = REBASE(0x1D9FF00);
    inline uint64_t luaD_throw = REBASE(0x4B68390);

    const uintptr_t TaskDefer = REBASE(0x1E95640);

    namespace reflections
    {
        const uintptr_t CastArgs = REBASE(0x1D370E0);
    }

    namespace Identity
    {
        const uintptr_t IdentityPtr = REBASE(0x8392B28);
    }

    namespace Signals
    {
        const uintptr_t FireTouchInterest = REBASE(0x2b25900);
        const uintptr_t DisconnectConnect = REBASE(0x1d5da50);
    }

    namespace Flags
    {
        const uintptr_t FireMouseClick = REBASE(0x26ADEE0);
        const uintptr_t FireRightMouseClick = REBASE(0x26AE550);
        const uintptr_t FireMouseHoverEnter = REBASE(0x26ae0f0);
        const uintptr_t FireMouseHoverLeave = REBASE(0x26ae2e0);
        const uintptr_t FireProximityPrompt = REBASE(0x26E9EC0);
        const uintptr_t TaskSchedulerTargetFps = REBASE(0x83A5638);
    }

    namespace Luau
    {
        const uintptr_t Luau_Execute = REBASE(0x4b7b430);
        const uintptr_t LuaO_NilObject = REBASE(0x6bc0438);
        const uintptr_t LuaH_DummyNode = REBASE(0x6bc02c8);
    }

    namespace DataModel
    {
        const uintptr_t Children = 0x70;
        const uintptr_t GameLoaded = 0x578;
        const uintptr_t ScriptContext = 0x440;
        const uintptr_t FakeDataModelToDataModel = 0x1D0;
        const uintptr_t FakeDataModelPointer = REBASE(0x7E26978);
    }

    namespace Extras
    {
        const uintptr_t k_table = REBASE(0x85A7390);
    }

    namespace ExtraSpace
    {
        const uintptr_t RequireBypass = 0x9D0;
        const uintptr_t ScriptContextToResume = 0x7D0;
    }

    namespace Scripts
    {
        const uintptr_t LocalScriptByteCode = 0x190;
        const uintptr_t ModuleScriptByteCode = 0x138;
    }

    namespace InstanceBridge
    {
        const uintptr_t Push = REBASE(0x1d48ca0);
    }

    namespace ClassDescriptor
    {
        const uintptr_t HashLookup = REBASE(0x5079d10);
        const uintptr_t GetProperty = REBASE(0xC8ACA0);
    }

    namespace RobloxThread
    {
        const uintptr_t IdentityPtr = REBASE(0x8392B28);
        const uintptr_t GetTlsPointer = REBASE(0x80E0);
    }

    namespace Hooks
    {
        const uintptr_t TaskScheduler = REBASE(0x836AAE8);//?
        const uintptr_t JobStart = 0xC8;
        const uintptr_t JobEnd = 0xD0;
        const uintptr_t JobTypeName = 0x108;
    }

    namespace Capabilities
    {
        const uintptr_t GetCapabilities = REBASE(0x4C2D260);
        const uintptr_t Capabilities = 0x28;
    }

    namespace Actor
    {
        inline const uintptr_t WriteLock = 0x720;
        const uintptr_t ParallelFlag = 0x100;
        const uintptr_t Parent = 0x68;
        inline const uintptr_t ResumeFacet = 0x7E0;
        const uintptr_t TaskDesynchronize = REBASE(0x1E95C80);
        const uintptr_t TaskSynchronize = REBASE(0x1E966A0);
    }

    namespace WaitSlot {
        constexpr uintptr_t checkPointer = 0x10;
        constexpr uintptr_t connectionRefs = 0x38;
        constexpr uintptr_t connectionRefs2 = 0x40;
        constexpr uintptr_t connectionRefs3 = 0x50;
        constexpr uintptr_t threadRefContainer = 0x18;
        constexpr uintptr_t threadRefContainer2 = 0x8;
        constexpr uintptr_t threadRefContainer3 = 0x10;
        constexpr uintptr_t threadRef = 0x20;
    }

    namespace Signal {
        constexpr uintptr_t next = 0x10;
        constexpr uintptr_t enabled = 0x20;
        constexpr uintptr_t signalSlot = 0x30;
        constexpr uintptr_t signalSlotWrapper = 0x38;

        namespace SignalSlotWrapper {
            constexpr uintptr_t Ptr = 0x10;
            constexpr uintptr_t secondPtr = 0x18;
            constexpr uintptr_t thirdPtr = 0x38;
        }

        namespace SignalSlot {
            constexpr uintptr_t isOnce = 0xB5;
            constexpr uintptr_t SignalRefs = 0x70;
            namespace Refs {
                constexpr uintptr_t luaThread = 0x8;
                constexpr uintptr_t luaThreadRefId = 0x10;
                constexpr uintptr_t functionRefId = 0x14;
            }
        }
    }

    namespace connection
    {
        const uintptr_t next = 0x10;
        const uintptr_t enabled = 0x20;
        const uintptr_t slot_wrapper = 0x30;
        const uintptr_t slot_wrapper_self = 0x38;
    }

    namespace slot_wrapper
    {
        const uintptr_t weak_object_ref = 0x60;
        const uintptr_t thread = 0x28;
        const uintptr_t function_id = 0x30;
    }

    namespace signal_slot
    {
        const uintptr_t is_once = 0x95;
    }

    namespace Instance
    {
        const uintptr_t PropertyDescriptorBitFlags = 0x8C;
        const uintptr_t Properties = 0x3C0;
        const uintptr_t ScriptableMask = 0x10;
        const uintptr_t ClassDescriptor = 0x18;
        const uintptr_t ClassName = 0x8;
        const uintptr_t Primitive = 0x128;
        const uintptr_t Overlap = 0x1f0;
        inline constexpr uintptr_t Name = 0x98;

    }
}

namespace Bytecode
{
    inline constexpr uintptr_t Pointer = 0x10;
    inline constexpr uintptr_t Size = 0x20;
    inline constexpr uintptr_t LocalScriptByteCode = 0x190;
    inline constexpr uintptr_t ModuleScriptByteCode = 0x138;

}

namespace Roblox
{
    inline auto LuaD_Throw = (void(__fastcall*)(lua_State*, int))Offsets::luaD_throw;
    inline uintptr_t* k_table = reinterpret_cast<uintptr_t*>(Offsets::Extras::k_table);
    inline auto Print = (uintptr_t(*)(int, const char*, ...))Offsets::Print;
    inline auto Luau_Execute = (void(__fastcall*)(lua_State*))Offsets::Luau::Luau_Execute;
    inline auto GetLuaStateForInstance = (lua_State * (__fastcall*)(uint64_t, uint64_t*, uint64_t*))Offsets::GetLuaStateForInstance;
    inline auto ScriptContextResume = (uint64_t(__fastcall*)(uint64_t, YieldState*, YieldingLuaThread**, uint32_t, uint8_t, uint64_t))Offsets::ScriptContextResume;

    inline LuaVMLoad_t LuaVMLoad = reinterpret_cast<LuaVMLoad_t>(Offsets::LuaVMLoad);

    namespace Signal
    {
        inline auto FireTouchInterest = (void(__fastcall*)(uintptr_t, uintptr_t, uintptr_t, bool, bool))Offsets::Signals::FireTouchInterest;
    }

    namespace InstanceBridge
    {
        inline auto UintPtr = (void(__fastcall*)(lua_State*, std::uintptr_t))Offsets::InstanceBridge::Push;
        inline auto Shared = (void(__fastcall*)(lua_State*, std::shared_ptr<std::uintptr_t*>))Offsets::InstanceBridge::Push;
        inline auto Void = (void(__fastcall*)(lua_State*, void**))Offsets::InstanceBridge::Push;
        inline auto Void2 = (void(__fastcall*)(lua_State*, void*))Offsets::InstanceBridge::Push;
        inline auto Weak = (void(__fastcall*)(lua_State*, std::weak_ptr<std::uintptr_t>))Offsets::InstanceBridge::Push;
    }

    using fireclick_t = void(__fastcall*)(void* clickDetector, float distance, void* player);
    inline auto FireMouseClick = reinterpret_cast<fireclick_t>(Offsets::Flags::FireMouseClick);
    inline auto FireRightMouseClick = reinterpret_cast<fireclick_t>(Offsets::Flags::FireRightMouseClick);

    using firehover_t = void(__fastcall*)(void* clickDetector, void* player);
    inline auto FireMouseHover = reinterpret_cast<firehover_t>(Offsets::Flags::FireMouseHoverEnter);
    inline auto FireMouseHoverLeave = reinterpret_cast<firehover_t>(Offsets::Flags::FireMouseHoverLeave);

    inline auto CastArgs = reinterpret_cast<uintptr_t(__fastcall*)(lua_State*, int, void*, bool, int)>(Offsets::reflections::CastArgs);
    inline auto GetCapabilities = (__int64(__fastcall*)(int*))Offsets::Capabilities::GetCapabilities;

    using TGetIdentityStruct = uintptr_t(__fastcall*)(uintptr_t);
    inline auto GetIdentityStruct = reinterpret_cast<TGetIdentityStruct>(Offsets::RobloxThread::GetTlsPointer);

    inline auto FireProximityPrompt = (void(__thiscall*)(uintptr_t))Offsets::Flags::FireProximityPrompt;
    inline auto FireTouchInterest = (void(__fastcall*)(uintptr_t, uintptr_t, uintptr_t, bool, bool))Offsets::Signals::FireTouchInterest;

    inline auto PushInstance = (void(__fastcall*)(lua_State*, void*))Offsets::InstanceBridge::Push;
    inline auto DisconnectConnection = (void(__fastcall*)(uintptr_t*))Offsets::Signals::DisconnectConnect;

    using GetPropertyT = uintptr_t(*)(uintptr_t, uintptr_t*);
    using HashLookupT = uintptr_t(*)(const char*);

    inline GetPropertyT GetProperty = reinterpret_cast<GetPropertyT>(Offsets::ClassDescriptor::GetProperty);
    inline HashLookupT HashLookup = reinterpret_cast<HashLookupT>(Offsets::ClassDescriptor::HashLookup);

    inline auto Void2 = reinterpret_cast<void(__fastcall*)(lua_State*, void*)>(Offsets::InstanceBridge::Push);

    using TaskDefer_t = int(__fastcall*)(lua_State*);
    inline TaskDefer_t TaskDefer = reinterpret_cast<TaskDefer_t>(Offsets::TaskDefer);
}