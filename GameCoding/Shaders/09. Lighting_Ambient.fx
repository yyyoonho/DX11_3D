#include "00. Global.fx"

float4 LightAmbient;	// 광원 고유 색
float4 MaterialAmbient;	// 물체 고유(=재질에 따른) 색 (=빛을 얼마나 받아줄건지)


VertexOutput VS(VertexTextureNormal input)
{
	VertexOutput output;
	output.position = mul(input.position,W);
	output.position = mul(output.position,VP);
	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}

Texture2D Texture0;

// Ambient(주변광/환경광)
// 수 많은 반사를 거쳐서 광원이 불분명한 빛
// 일정한 밝기와 색으로 표현
float4 PS(VertexOutput input) : SV_TARGET
{
	float4 color = LightAmbient * MaterialAmbient;
	//return color;
	return Texture0.Sample(LinearSampler, input.uv) * color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};