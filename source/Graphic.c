/*
*   	2014年12月29日11:09:11
*	V1.0 	By Breaker
*
*	文件名：Graphic.c
*	定义所有图像处理相关的函数
*	
*/

#include "Global.h"
#include "Graphic.h"
#include "GPU.h" 
#include "stdarg.h"

// screen_width  screen_high  color_deep
void init_screen_layer()
{
	RGB_24Bit *buf;
	struct picture NewPicture;
	int PicIndex;
	
	GpuInfoAddr = init_GPU(screen_width, screen_high, color_deep);

	//if(GpuInfoAddr == 0)
	{
		//return -1; /*初始化GPU发生错误*/
	}

	GpuBufAddr =  (volatile unsigned char *)(*(unsigned int *)(GpuInfoAddr + 32));
	
	colorBlack.R = 0x00;
	colorBlack.G = 0x00;
	colorBlack.B = 0x00;
	
	colorWrite.R = 0xFF;
	colorWrite.G = 0xFF;
	colorWrite.B = 0xFF;
	
	colorRed.R  = 0xFF;
	colorRed.G  = 0x00;
	colorRed.B  = 0x00;
	
	colorGreen.R  = 0x00;
	colorGreen.G  = 0xFF;
	colorGreen.B  = 0x00;
	
	colorBule.R  = 0x00;
	colorBule.G  = 0x00;
	colorBule.B  = 0xFF;
	
	colorF.R = 0xFF;
	colorF.G = 0xFF;
	colorF.B = 0xFF;
	
	colorB.R = 0x28;
	colorB.G = 0x82;
	colorB.B = 0xE6;
	
	buf = os_malloc((screen_width  * screen_high  * color_deep) / 8 );
	NewPicture.buf = buf;
	NewPicture.Position.top = 0;
	NewPicture.Position.left = 0;
	NewPicture.Position.width = screen_width;
	NewPicture.Position.hight = screen_high;
	
	//蓝色背景
	//boxfill8(buf, NewPicture.Position.width, COL8_2882E6, 0, 0, NewPicture.Position.width - 1, NewPicture.Position.hight - 15);
	//boxfill8(buf, NewPicture.Position.width, COL8_C6C6C6, 0, NewPicture.Position.hight - 14, NewPicture.Position.width - 1, NewPicture.Position.hight - 13);
	//boxfill8(buf, NewPicture.Position.width, COL8_FFFFFF, 0, NewPicture.Position.hight - 13, NewPicture.Position.width - 1, NewPicture.Position.hight - 12);
	//boxfill8(buf, NewPicture.Position.width, COL8_C6C6C6, 0, NewPicture.Position.hight - 12, NewPicture.Position.width - 1, NewPicture.Position.hight - 1);

	//白色
	//boxfill8(buf, NewPicture.Position.width, COL8_FFFFFF, 2, NewPicture.Position.hight - 11, 25, NewPicture.Position.hight - 11);
	//boxfill8(buf, NewPicture.Position.width, COL8_FFFFFF, 1, NewPicture.Position.hight - 11, 1, NewPicture.Position.hight - 2);

	//黑色阴影
	//boxfill8(buf, NewPicture.Position.width, COL8_000000, 2, NewPicture.Position.hight - 1, 25, NewPicture.Position.hight - 1);
	//boxfill8(buf, NewPicture.Position.width, COL8_000000, 25, NewPicture.Position.hight - 11, 25, NewPicture.Position.hight - 2);

	//灰色阴影
	//boxfill8(buf, NewPicture.Position.width, COL8_2882E6, 26, NewPicture.Position.hight - 11, 26, NewPicture.Position.hight - 1);

	
	DrawBlock((RGB_24Bit *) buf,  colorB, 0, 0, screen_width, screen_high);
	DesktopHandle = add_pic(NewPicture);
	if(DesktopHandle != -1)
	{
		add_pic_to_layer(DesktopHandle);
		//pic_layer_reflash();
	}

}

/*****************************************************
*	2014年12月29日11:11:14
*	V2.0 	By Breaker
*
*	int init_screen(unsigned int width, unsigned int height, unsigned int bitDepth)
*   	初始化桌面，显示任务栏等基本信息
*	return 0 成功  -1 失败	
*/

int init_screen(unsigned int width, unsigned int height, unsigned int bitDepth)
{
	
	RGB_24Bit color;
	int top,left;
	
	GpuInfoAddr = init_GPU(width, height, bitDepth);

	if(GpuInfoAddr == 0)
	{
		return -1; /*初始化GPU发生错误*/
	}

	GpuBufAddr =  (volatile unsigned char *)(*(unsigned int *)(GpuInfoAddr + 32));
	
	colorBlack.R = 0x00;
	colorBlack.G = 0x00;
	colorBlack.B = 0x00;
	
	colorWrite.R = 0xFF;
	colorWrite.G = 0xFF;
	colorWrite.B = 0xFF;
	
	colorRed.R  = 0xFF;
	colorRed.G  = 0x00;
	colorRed.B  = 0x00;
	
	colorGreen.R  = 0x00;
	colorGreen.G  = 0xFF;
	colorGreen.B  = 0x00;
	
	colorBule.R  = 0x00;
	colorBule.G  = 0x00;
	colorBule.B  = 0xFF;
	
	colorF.R = 0xFF;
	colorF.G = 0xFF;
	colorF.B = 0xFF;
	
	colorB.R = 0x28;
	colorB.G = 0x82;
	colorB.B = 0xE6;
	
	DrawBlock((RGB_24Bit *) GpuBufAddr,  colorB, 0, 0, screen_width, screen_high);
	return 0;
}

/*****************************************************
*	2014年12月29日16:57:16
*	V1.0 	By Breaker
*
*	void DrawDot(void * to_addr, RGB_24Bit color, int top, int left)
*   	画点
*	return void 超出显示范围退出	
*/

void DrawDot(RGB_24Bit * to_addr, RGB_24Bit color, int top, int left)
{
	/*检查*/
	//if(top > (((struct FrameBufferInfoS *)GpuInfoAddr)->phyHeight) || top < 0)
	{
	//	return;
	}

	//if(left > (((struct FrameBufferInfoS *)GpuInfoAddr)->phyWidth) || left < 0)
	{
	//	return;
	}
	
	//*(volatile unsigned char *)((unsigned int)GpuBufAddr + (((((struct FrameBufferInfoS *)GpuInfoAddr)->phyWidth) * top + left) * 3 ))= color.R;
	//*(volatile unsigned char *)((unsigned int)GpuBufAddr + (((((struct FrameBufferInfoS *)GpuInfoAddr)->phyWidth) * top + left) * 3 + 1))= color.G;	
	//*(volatile unsigned char *)((unsigned int)GpuBufAddr + (((((struct FrameBufferInfoS *)GpuInfoAddr)->phyWidth)* top + left) * 3 + 2))= color.B;	
	u8 * base_addr  = (u8 *)((screen_width * top + left)  + to_addr);
	*(u8 *)base_addr = color.R;
	*((u8 *)base_addr + 1) = color.G;
	*((u8 *)base_addr + 2)= color.B;
}

/*****************************************************
*	2014年12月29日16:57:16
*	V1.0 	By Breaker
*
*	    void DrawDot_to_layer(RGB_24Bit * to_addr, RGB_24Bit color ,int width, int top, int left)
*   	画点
*	return void 超出显示范围退出
*/

void DrawDot_to_layer(RGB_24Bit * to_addr, RGB_24Bit color ,int width, int top, int left)
{

	u8 * base_addr  = (u8 *)((width * top + left)  + to_addr);
	*(u8 *)base_addr = color.R;
	*((u8 *)base_addr + 1) = color.G;
	*((u8 *)base_addr + 2)= color.B;
}

int DrawLine(RGB_24Bit color, int x1, int y1, int x2, int y2)
{
	return 0;
}

/*****************************************************
*	2014年12月29日16:58:27
*	V1.0 	By Breaker
*
*	void DrawBlock(RGB_24Bit color, int top, int left, unsigned int width, unsigned int height)
*   	填充
*	return void 超出显示范围退出	
*/
void DrawBlock(RGB_24Bit * to_addr, RGB_24Bit color, int top, int left, unsigned int width, unsigned int height)
{
	int top_t,left_t;
	for(top_t=0; top_t < height; top_t++)
	{
		for(left_t=0; left_t < width; left_t++)
		{
			DrawDot(to_addr, color, top+top_t, left+left_t);
		}
	}
}

int DrawBlockByMemory()
{
	return 0;
}



/*****************************************************
*	2014年12月29日16:58:27
*	V1.0 	By Breaker
*
*	void drawCharacter(unsigned char ASC2, RGB_24Bit color, int *top, int *left)
*   	显示字体
*	return void 	
*/
void drawCharacter(RGB_24Bit * to_addr, unsigned char ASC2, RGB_24Bit color, int *top, int *left)
{
	int row;
	char data;
	unsigned char *ASC2_addr;
	/*检查*/
	if( ASC2 > 128 )
	{
		return;
	}
	
	/*计算参数字符字体所在的首地址*/
	ASC2_addr = (unsigned char *)((unsigned int)font + (ASC2 * 16));
	for (row = 0; row < 16; row++)
	{
		data = ASC2_addr[row];
		if ((data & 0x80) != 0) DrawDot(to_addr , color, *top+row, *left + 7);
		if ((data & 0x40) != 0) DrawDot(to_addr, color, *top+row, *left + 6);
		if ((data & 0x20) != 0) DrawDot(to_addr, color, *top+row, *left + 5);
		if ((data & 0x10) != 0) DrawDot(to_addr, color, *top+row, *left + 4);
		if ((data & 0x08) != 0) DrawDot(to_addr, color, *top+row, *left + 3);
		if ((data & 0x04) != 0) DrawDot(to_addr, color, *top+row, *left + 2);
		if ((data & 0x02) != 0) DrawDot(to_addr, color, *top+row, *left + 1);
		if ((data & 0x01) != 0) DrawDot(to_addr, color, *top+row, *left + 0);
	}
	*left += 8;
}

/*****************************************************
*	2014年12月31日17:36:55
*	V1.0 	By Breaker
*
*	void drawString(RGB_24Bit * to_addr, char *string, RGB_24Bit color, int *top, int *left)
*   	显示字符串
*	return void 	
*/
void drawString(RGB_24Bit * to_addr, char *string, RGB_24Bit color, int *top, int *left)
{
	while(*string != 0)
	{
		drawCharacter(to_addr, *string, color, top, left);
		
		string++;
		/*计算下次显示字符的位置*/
		//left = left + 8;
	}
}

/*****************************************************
*	2015年01月01日16:34:02
*	V1.0 	By Breaker
*
*	void drawDec(RGB_24Bit * to_addr, int dec, RGB_24Bit color, int *top, int *left)
*   	显示十进制数字，drawStringF()子函数
*	return void 	
*/
void drawDec(RGB_24Bit * to_addr, int dec, RGB_24Bit color, int *top, int *left)
{
	
	int times = 10;
	while( dec / times != 0)
	{
		times *= 10;
	}
	
	times /= 10;
	
	do {
		unsigned char num = 0;
		num = (unsigned char ) (dec / times);
		drawCharacter(to_addr,  (num + '0'), color, top, left );
		dec -=  num * times;
		times /= 10;
	}while(times != 0);
}

/*****************************************************
*	2015年01月02日14:07:24
*	V1.0 	By Breaker
*
*	void drawFlt(double flt, RGB_24Bit color, int *top, int *left);
*	显示浮点数，drawStringF()子函数
* 	别的文件不能调用参数列表中含有浮点型数据的函数，很奇怪。
* 	格式化显示浮点型数据还是没有弄好，总会出现一些很奇怪的
* 	问题。弄这个函数两天了，先放着吧。调试显示浮点数不是很多
*	return void 	
*/
/*2015年01月01日22:59:23  真是一个奇怪的bug，函数参数不能有double类型。Why?*/
void drawFlt(float  flt, RGB_24Bit color, int *x, int *y)
{

	//int tmpintA = 0;
	//int tmpintB = 0;
	
	//tmpintA = (int) flt ;
	//tmpintB =  (int )  ((flt - tmpintA) * 10000000) ;
	//test_drawFlt_sub0(color, x, y, tmpintA, tmpintB);
	//drawDec(a, color, x, y);
	//drawCharacter('.', color, x, y);
	//drawDec(b, color, x, y);
}


/*****************************************************
*	2015年01月02日14:01:53
*	V1.0 	By Breaker
*
*	void drawHex(RGB_24Bit to_add, int hex, RGB_24Bit color, char IS_Big,int *top, int *left)
*   	显示十六进制数字，drawStringF()子函数
*	return void 	
*/
void drawHex(RGB_24Bit * to_addr, int hex, RGB_24Bit color, char IS_Big,int *top, int *left)
{
	int times = 16;
	while( hex / times != 0)
	{
		times *= 16;
	}
	
	times /= 16;
	
	do {
		unsigned char num = 0;
		num = (unsigned char ) (hex / times);
		if(num < 10)
		{
			drawCharacter(to_addr, (num + '0'), color, top, left );
		}
		else
		{
			num -= 10;
			if( IS_Big == 1)
			{
				drawCharacter( to_addr,(num + 'A'), color, top, left );
			}
			else
			{
				drawCharacter( to_addr, (num + 'a'), color, top, left );
			}
			
		}
		
		hex -=  num * times;
		times /= 16;
	}while(times != 0);
}


/*****************************************************
*	2015年01月02日14:01:53
*	V1.0 	By Breaker
*
*	void drawBin(RGB_24Bit to_add, int bin, RGB_24Bit color, char IS_Big,int *top, int *left)
*   	显示十六进制数字，drawStringF()子函数
*	return void 	
*/
void drawBin(RGB_24Bit * to_addr, int bin, RGB_24Bit color, char IS_Big,int *top, int *left)
{
	int times = 2;
	while( bin / times != 0)
	{
		times *= 2;
	}
	
	times /= 2;
	
	do {
		unsigned char num = 0;
		num = (unsigned char ) (bin / times);
		drawCharacter(to_addr,  (num + '0'), color, top, left );
		bin -=  num * times;
		times /= 2;
	}while(times != 0);
}

/*****************************************************
*	2015年01月01日11:18:22
*	V1.0 	By Breaker
*
*	void drawStringF(RGB_24Bit * to_addr, char *fmt, RGB_24Bit color, int top, int left, ...)
*   	格式化显示字符串
*	return void 	
*/
void drawStringF(RGB_24Bit * to_addr, char *fmt, RGB_24Bit color, int top, int left, ...)
{
	/*  */
	double vargflt = 0;
	int  vargint = 0;
	char* vargpch = 0;
	char vargch = 0;
	char* pfmt = 0;
	va_list vp;
	
	/*left 后第一个参数*/
	va_start(vp, left);
	pfmt = fmt;
	
	 while(*pfmt)
	{
		if(*pfmt == '%')
		{
			switch(*(++pfmt))
			{
				case 'c':
					vargch = va_arg(vp, int); 
					drawCharacter(to_addr, vargint, color, &top, &left);
					break;
				case 'd':
				case 'i':
					vargint = va_arg(vp, int);
					drawDec(to_addr, vargint,color, &top, &left);
					break;
				case 'f':
					vargflt = va_arg(vp, double);
					//drawFlt(vargflt,color, &top, &left);
					break;
				case 's':
					vargpch = va_arg(vp, char*);
					drawString(to_addr, vargpch,color, &top, &left);
					break;
				case 'b':
				case 'B':
					vargint = va_arg(vp, int);
					drawBin(to_addr, vargint,color, 0,&top, &left);
					break;
				case 'x':
					vargint = va_arg(vp, int);
					drawHex(to_addr, vargint,color, 0,&top, &left);
					break;
				case 'X':
					vargint = va_arg(vp, int);
					drawHex(to_addr, vargint,color, 1,&top, &left);
					break;
				case '%':
					drawCharacter(to_addr, '%', color, &top, &left );
					break;
				default:
					break;
			}
			pfmt++;
		}
		else
		{
			drawCharacter(to_addr, *pfmt++, color, &top, &left );
		}	
	}
	va_end(vp);
}


/*****************************************************
*	2015年01月14日22:17:15
*	V1.0 	By Breaker
*
*	void os_printf(char *fmt, ...)
*   	格式化显示字符串
*	return void 	
*/
void os_printf(char *fmt, ...)
{
	/*  */
	double vargflt = 0;
	int  vargint = 0;
	char* vargpch = 0;
	char vargch = 0;
	char* pfmt = 0;
	va_list vp;
	
	RGB_24Bit color;
	color.R=0xFF;
	color.G=0xFF;
	color.B=0xFF;
	
	/*fmt 后第一个参数*/
	va_start(vp, fmt);
	pfmt = fmt;
	
	 while(*pfmt)
	{
		if(*pfmt == '%')
		{
			switch(*(++pfmt))
			{
				case 'c':
					vargch = va_arg(vp, int); 
					drawCharacter((RGB_24Bit * ) GpuBufAddr, vargint, color, &os_top, &os_left);
					break;
				case 'd':
				case 'i':
					vargint = va_arg(vp, int);
					drawDec((RGB_24Bit * ) GpuBufAddr, vargint,color, &os_top, &os_left);
					break;
				case 'f':
					vargflt = va_arg(vp, double);
					//drawFlt(vargflt,color, &os_top, &left);
					break;
				case 's':
					vargpch = va_arg(vp, char*);
					drawString((RGB_24Bit * ) GpuBufAddr, vargpch,color, &os_top, &os_left);
					break;
				case 'b':
				case 'B':
					vargint = va_arg(vp, int);
					drawBin((RGB_24Bit * ) GpuBufAddr, vargint,color, 0,&os_top, &os_left);
					break;
				case 'x':
					vargint = va_arg(vp, int);
					drawHex((RGB_24Bit * ) GpuBufAddr, vargint,color, 0,&os_top, &os_left);
					break;
				case 'X':
					vargint = va_arg(vp, int);
					drawHex((RGB_24Bit * ) GpuBufAddr, vargint,color, 1,&os_top, &os_left);
					break;
				case 'n':
					os_top +=16;
					os_left = 0;
					break;
				case '%':
					drawCharacter((RGB_24Bit * ) GpuBufAddr, '%', color, &os_top, &os_left );
					break;
				default:
					break;
			}
			pfmt++;
		}
		else
		{
			drawCharacter((RGB_24Bit * ) GpuBufAddr, *pfmt++, color, &os_top, &os_left );
		}	
	}
	va_end(vp);
}


/*-----------------------------------------------图层处理 Layer-----------------------------------------------------------------------*/

/*
*	2014年12月13日16:04:16
*	V1.0 	By Breaker
*
*	 根据所给缓冲区和位置将图像画到屏幕
*	void draw_to_screen(struct picture NewPicture)
*	return  void
*/
void draw_to_screen(struct picture NewPicture)
{
		//u32 to_addr = (u32) GpuBufAddr  + ( ( NewPicture.Position.top * screen_width +  NewPicture.Position.left ) * ( color_deep / 8));
		//u32 size = NewPicture.Position.hight *  NewPicture.Position.width * (( color_deep / 8));
		//os_memcpy((u32)NewPicture.buf , to_addr  , size);

		int top, left ;
		RGB_24Bit temp_color;
		u32 i = 0;
		char * base_addr = (char *) NewPicture.buf;
		for(top = 0; top < NewPicture.Position.hight; top++)
		{
			for(left = 0; left < NewPicture.Position.width; left++)
			{
				temp_color.R = base_addr[i];
				temp_color.G = base_addr[i+1];
				temp_color.B = base_addr[i +2];
				DrawDot((RGB_24Bit *)GpuBufAddr, temp_color, NewPicture.Position.top + top, NewPicture.Position.left + left) ;
				i += 3;
			}
		}

		return;
}

/*
*	2014年12月13日09:51:14
*	V1.0 	By Breaker
*
*	初始化图层表
*	struct pic_layer_table  *PicLayerTable_init();
*	return  图层表首地址
*/
struct pic_layer_table  *PicLayerTable_init()
{
	int i = 0;
	struct pic_layer_table *addr = 0;

	addr = os_malloc(sizeof(struct pic_layer_table));
	for(i=0; i < MaxPicLayer; i++)
	{
		//(addr->PicLayer[i]).Empty = 1;
		addr->Picture[i].Empty = 1;
	}
	addr->LayerCount = 0;
	addr->PicCount = 0;
	
	return addr;
}


/*
*	2014年12月13日09:08:07
*	V1.0 	By Breaker
*
*	添加新图片并返回句柄
*	unsigned char add_pic(struct picture NewPicture);
*	return  图片句柄
*/

unsigned char add_pic(struct picture NewPicture)
{
	int i, handle = -1;
	if( PicLayerTable->PicCount >= MaxPicLayer )
	{
		return handle;  //错误，图层表已经添加满，无法再继续添加
	}
	
	for(i=0; i<MaxPicLayer; i++)
	{
		if(PicLayerTable->Picture[i].Empty == 1)
		{
			handle = i;	//获取到句柄
			break;
		}
	}
	
	//正确获取到句柄，将其复制进 PicLayerTable
	PicLayerTable->Picture[i] = NewPicture;
	PicLayerTable->Picture[i].Empty = 0;
	PicLayerTable->PicCount++;
	return handle;
}

/*
*	2014年12月13日11:01:28
*	V1.0 	By Breaker
*
*	将图片放入最上层 
*	unsigned char add_pic_to_layer(unsigned char PicIndex);
*	return  是否成功
*/
unsigned char add_pic_to_layer(unsigned char PicIndex)   //   放在当前最上层  
{
	if( PicLayerTable->LayerCount >= MaxPicLayer )	  //图层分配完，返回错误
	{
		return -1;
	}
	else
	{
		PicLayerTable->PicLayer[PicLayerTable->LayerCount].PicIndex = PicIndex;   //连线
		PicLayerTable->Picture[PicIndex].LayerIndex = PicLayerTable->LayerCount;
		//PicLayerTable->PicLayer[PicLayerTable->LayerCount].Empty = 0; 
	}
	
	PicLayerTable->LayerCount++;
	return PicLayerTable->LayerCount - 1;
}

/*
*	2014年12月13日14:26:41
*	V1.0 	By Breaker
*
*	删除 picture
*	int rm_picture(unsigned char PicIndex);
*	return  是否成功
*/
int rm_picture(unsigned char PicIndex)
{
	if((PicIndex < 0) || (PicIndex >= MaxPicLayer) )
	{
		return -1;
	}
	else
	{
		PicLayerTable->Picture[PicIndex].Empty = 1;
		PicLayerTable->PicCount--;
		return 0;
	}
}

/*
*	2014年12月13日14:26:41
*	V1.0 	By Breaker
*
*	清空图片所在图层
*	int rm_from_layer(unsigned char PicIndex);
*	return  是否成功
*/
int rm_from_layer(unsigned char PicIndex)
{
	int i,LayerIndex;
	LayerIndex = get_LayerIndex_by_PicIndex(PicIndex);
	if((LayerIndex < 0) || (LayerIndex >=  PicLayerTable->LayerCount) )
	{
		return -1;
	}
	
	for(i = LayerIndex + 1; i <  PicLayerTable->LayerCount; i++)
	{
		PicLayerTable->PicLayer[i-1] = PicLayerTable->PicLayer[i];	//前移
	}
	PicLayerTable->LayerCount--;
	return 0;
}



/*
*	2014年12月13日14:04:22
*	V1.0 	By Breaker
*
*	通过 PicIndex获取 LayerIndex 
*	unsigned char get_LayerIndex_by_PicIndex(unsigned char PicIndex);
*	return  LayerIndex 
*/
unsigned char get_LayerIndex_by_PicIndex(unsigned char PicIndex)
{
	return PicLayerTable->Picture[PicIndex].LayerIndex;
}

/*
*	2014年12月13日14:07:16
*	V1.0 	By Breaker
*
*	通过 LayerIndex获取 PicIndex
*	unsigned get_PicIndex_by_LayerIndex(unsigned char LayerIndex);
*	return  PicIndex 
*/
unsigned char get_PicIndex_by_LayerIndex(unsigned char LayerIndex)
{
	return PicLayerTable->PicLayer[LayerIndex].PicIndex;
}

/*
*	2014年12月13日15:17:21
*	V1.0 	By Breaker
*
*	变换图层
*	int set_pic_layer(unsigned char PicIndex,unsigned char LayerIndex)
*	return  是否成功 
*/
int set_pic_layer(unsigned char PicIndex,unsigned char LayerIndex)
{
	int i = 0;
	
	// 分两步 1.从原来位置拿出
	if(rm_from_layer(PicIndex)  != 0)
	{
		return -1;
	}
	
	// 2. 插入相应位置
	PicLayerTable->LayerCount++;
	for(i = PicLayerTable->LayerCount ; i < LayerIndex; i--)
	{
		PicLayerTable->PicLayer[i] = PicLayerTable->PicLayer[i-1];	//前移
	}
	PicLayerTable->PicLayer[LayerIndex].PicIndex = PicIndex;
	
	return 0;
}

/*
*	2014年12月13日15:36:40
*	V1.0 	By Breaker
*
*	将 picture 放到指定位置
*	int set_picture_position(unsigned char PicIndex, struct position Position)
*	return  是否成功 
*/
int set_picture_position(unsigned char PicIndex, struct position Position)
{
	if( (PicIndex < 0) || (PicIndex >=  MaxPicLayer) || (PicLayerTable->Picture[PicIndex].Empty == 1))
	{
		return -1;
	}
	PicLayerTable->Picture[PicIndex].Position = Position;
	return 0;
}

/*
*	2014年12月13日15:57:28
*	V1.0 	By Breaker
*
*	刷新图像
*	int pic_layer_reflash();
*	return  是否成功 
*/
void pic_layer_reflash()
{
	blink_GPIO19();
	int i;
	unsigned char PicIndex;
	for(i=0; i < PicLayerTable->LayerCount; i++)
	{
		PicIndex = get_PicIndex_by_LayerIndex(i);
		if(PicLayerTable->Picture[PicIndex].Empty == 0)
		{
			draw_to_screen(PicLayerTable->Picture[PicIndex]);
			//os_printf("PicIndex :<%d>", PicIndex);
			
		}
	}
}

