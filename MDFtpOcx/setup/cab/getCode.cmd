cd C:\Program Files\Microsoft Visual Studio 8\SDK\v2.0\Bin
c:
makecert   /sv   "diyOnline.PVK"   /n   "CN=南京欣网视讯信息技术有限公司"   diyOnline.cer 
cert2spc   diyOnline.cer   diyOnline.spc
