#include "defines.h"
#include "cInstance.h"

cInstance::cInstance(LPDIRECT3DDEVICE9 pDevice) :
m_pDevice(pDevice),
m_vScale(1,1,1),
m_vPos(0,0,0)
{

}

cInstance::~cInstance(void)
{
}
