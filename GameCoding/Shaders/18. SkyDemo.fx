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


	// 어차피 SkyBox용 구체는 월드좌표가 카메라와 동일하다.
	// 즉, W 연산 생략가능.
	float4 viewPos = mul(float4(input.position.xyz, 0), V);
	float4 clipSpacePos = mul(viewPos, P);

	// P연산 이후 자동으로 xy[-1~1] z[0~1] 범위를 맞춰주기 위해
	// z의 값을 w에 저장한 후 w로 xyzw를 각각 나눠주는데,
	// 임의로
	// SkyBox는 각 픽셀의 깊이값(z)가 거의 1(맨끝)에 닿을 수 있게
	// z를 w로 넣어준다.
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
