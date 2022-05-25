#include <stdio.h>
#include <string>
#include <Windows.h>
#include <initguid.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <audiopolicy.h>

extern "C"
{
    __declspec(dllexport) void SetAppVolume(int appIndex, int level);
}

void SetAppVolume(int appIndex, int level)
{
    HRESULT result = CoInitialize(NULL);

    CLSID clsid = __uuidof(MMDeviceEnumerator); //This Class
    IID iid = __uuidof(IMMDeviceEnumerator); //This Interface
    IMMDeviceEnumerator* deviceList = NULL;
    IMMDevice* output = NULL;
    IAudioSessionManager2* manager = NULL;
    IAudioSessionEnumerator* sessionList = NULL;

    result = CoCreateInstance(clsid, NULL, CLSCTX_ALL, iid, (void**)&deviceList);
    deviceList->GetDefaultAudioEndpoint(EDataFlow::eRender, ERole::eMultimedia, &output);

    iid = __uuidof(IAudioSessionManager2);
    output->Activate(iid, NULL, NULL, (void**)&manager);
    manager->GetSessionEnumerator(&sessionList);

    int count = 0;
    sessionList->GetCount(&count);
    ISimpleAudioVolume* volumeControl;
    for (int i = 0; i < count; ++i)
    {
        IAudioSessionControl* control;
        sessionList->GetSession(i, &control);
        if (i == appIndex)
        {
            control->QueryInterface(IID_PPV_ARGS(&volumeControl));
            volumeControl->SetMasterVolume((float)level / 100.0f, NULL);
        }
        control->Release();
    }

    sessionList->Release();
    manager->Release();
    output->Release();
    deviceList->Release();

    CoUninitialize();
}