#ifndef __ADTILEDMANAGER_H_
#define __ADTILEDMANAGER_H_

//-----------------------------------------------------------------------------
class AdTiledManager {
private:
	static duk_context* s_pJSCtx;
	static int          s_iInstances;

protected:
	int   m_iWidth;
	int   m_iHeight;
	int   m_nLayers;
	int** m_pIndices;

protected:
	void Unload(void);

public:
	int N(void)      {return m_nLayers;}
	int Width(void)  {return m_iWidth;}
	int Height(void) {return m_iHeight;}

public:
	void Load(const char* pName);

public:
	int* GetLayer(int l) {return m_pIndices[l];}

	int GetTile(int iLayer, int iIndex) {
		if(!m_pIndices        ||
			iIndex<0          ||
			iLayer<0          ||
			iLayer>=m_nLayers ||
			iIndex>=(m_iWidth*m_iHeight)
		) return 0;
		return m_pIndices[iLayer][iIndex];
	}

	int GetTile(int iLayer, int iX, int iY) {
		int iIndex = (iY*m_iWidth)+iX;
		return GetTile(iLayer, iIndex);
	}

public:
	AdTiledManager(void);
	~AdTiledManager(void);
};

#endif
