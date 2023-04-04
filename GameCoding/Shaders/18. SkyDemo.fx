#include "00. Global.fx"
#include "00. Light.fx"

struct VS_OUT
{
	float4 position : SV_POSITION;
	float2  uv : TEXCOORD;
};

VS_OUT VS(VertexTextureNormalTangent input)
{
	VS_OUT output;


	// ������ SkyBox�� ��ü�� ������ǥ�� ī�޶�� �����ϴ�.
	// ��, W ���� ��������.
	float4 viewPos = mul(float4(input.position.xyz, 0), V);
	float4 clipSpacePos = mul(viewPos, P);

	// P���� ���� �ڵ����� xy[-1~1] z[0~1] ������ �����ֱ� ����
	// z�� ���� w�� ������ �� w�� xyzw�� ���� �����ִµ�,
	// ���Ƿ�
	// SkyBox�� �� �ȼ��� ���̰�(z)�� ���� 1(�ǳ�)�� ���� �� �ְ�
	// z�� w�� �־��ش�.
	output.position = clipSpacePos.xyzw;
	output.position.z = output.position.w * 0.999999f;

	output.uv = input.uv;

	return output;
}

float4 PS(VS_OUT input) : SV_TARGET
{
	float color = DiffuseMap.Sample(LinearSampler, input.uv);
	return color;
}

technique11 T0
{
	pass P0
	{
		SetRasterizerState(FrontCounterClockwiseTrue);
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
};
