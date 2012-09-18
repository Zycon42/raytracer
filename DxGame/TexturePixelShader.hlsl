Texture2D shaderTexture;
SamplerState SampleType;

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 tex: TEXCOORD0;
};

float4 main(PixelInput input) : SV_TARGET
{
	return shaderTexture.Sample(SampleType, input.tex);
}