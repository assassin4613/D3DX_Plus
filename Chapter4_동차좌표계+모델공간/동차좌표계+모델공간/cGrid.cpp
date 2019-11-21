#include "defines.h"

cGrid::cGrid(void)
{
}

cGrid::~cGrid(void)
{
}

void cGrid::Init(LPDIRECT3DDEVICE9 pDevice, int width, int height, float scale, DWORD color )
{
	m_pDevice = pDevice;

	int		cntX = (int)(width / scale) + 1;
	int		cntY = (int)(height / scale) + 1;

	int lineCount = cntX * cntY;
	int totalCount = lineCount * 2;

	SVertex*	pVertex = new SVertex[ totalCount];
	memset( pVertex, 0, sizeof( SVertex ) * totalCount );

	float startX = -width / 2.f;
	float startZ = height / 2.f;

	for( int i = 0 ; i < cntX ; i++ )
	{
		pVertex[i * 2].vPos.x = startX;
		pVertex[i * 2].vPos.y = 0.f;
		pVertex[i * 2].vPos.z = startZ - i * scale;
		pVertex[i * 2].color = color;

		pVertex[i * 2 + 1].vPos.x = startX + width;
		pVertex[i * 2 + 1].vPos.y = 0.f;
		pVertex[i * 2 + 1].vPos.z = startZ - i * scale;
		pVertex[i * 2 + 1].color = color;
	}

	int j = 0;
	for( int i = cntX ; i < cntX + cntY ; i++, j++ )
	{
		pVertex[i * 2].vPos.x = startX + j * scale;
		pVertex[i * 2].vPos.y = 0.f;
		pVertex[i * 2].vPos.z = startZ;
		pVertex[i * 2].color = color;

		pVertex[i * 2 + 1].vPos.x = startX + j * scale;
		pVertex[i * 2 + 1].vPos.y = 0.f;
		pVertex[i * 2 + 1].vPos.z = startZ - height;
		pVertex[i * 2 + 1].color = color;
	}

	m_pDevice->CreateVertexBuffer( sizeof( SVertex ) * totalCount,
		0, SVertex::CUSTOM_FVF, D3DPOOL_MANAGED, &m_pVB, 0);


	void* pData = NULL;

	m_pVB->Lock( 0, sizeof(SVertex) * totalCount,
				&pData, 0 );

	memcpy( pData, pVertex, sizeof(SVertex) * totalCount );

	m_pVB->Unlock();

	delete [] pVertex;

	m_LineCount = lineCount;
}

void cGrid::Render()
{
	m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof( SVertex ));
	m_pDevice->SetFVF(SVertex::CUSTOM_FVF );
	m_pDevice->DrawPrimitive( D3DPT_LINELIST,0, m_LineCount);
}

void cGrid::Release()
{
	SAFE_RELEASE( m_pVB );
}