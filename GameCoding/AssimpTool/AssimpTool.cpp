#include "pch.h"
#include "AssimpTool.h"
#include "Converter.h"

void AssimpTool::Init()
{
	{
		shared_ptr<Converter> converter = make_shared<Converter>();

		// FBX -> Memory
		converter->ReadAssetFile(L"Tank/Tank.fbx");

		// Memory -> CustomData(File)
		converter->ExportMaterialData(L"Tank/Tank");
		converter->ExportModelData(L"Tank/Tank");

		// Customdata(File) -> Memory

	}

	{
		shared_ptr<Converter> converter = make_shared<Converter>();

		// FBX -> Memory
		converter->ReadAssetFile(L"Tower/Tower.fbx");

		// Memory -> CustomData(File)
		converter->ExportMaterialData(L"Tower/Tower");
		converter->ExportModelData(L"Tower/Tower");

		// Customdata(File) -> Memory

	}
}

void AssimpTool::Update()
{

}

void AssimpTool::Render()
{

}
