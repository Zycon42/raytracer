struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 tex: TEXCOORD0;
};

PixelInput main( float4 pos : POSITION, float2 tex : TEXCOORD0 )
{
	PixelInput ret;
	ret.pos = pos;
	ret.tex = tex;
	return ret;
}
