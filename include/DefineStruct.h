#pragma once
#pragma pack(1) // 이 부분이 없으면 아키텍처의 버스의 배수로 스트럭처 사이즈가 잡힌다.

/// <summary>
/// 
/// x86에서 STDATA 사이즈는 76이고 x64에서 STDATA 사이즈는 80이다
/// 이 차이는 UINT_PTR에서 발생한 것으로 x64에서는 포인터 사이즈는 8바이트이다.
/// 
/// copydata로 다른 아키텍처로 보내는 테스트 결과는 
/// 포인터 변수를 제외하면 다른 아키텍처로 정상적으로 데이터 송수신이 가능하다.
/// 
/// </summary>

struct STDATA
{
	char str1[20];		// size:20
	WCHAR str2[20];		// size:40
	int num1;			// size:4
	DWORD num2;			// size:4
	UINT_PTR num3;		// size:4 (x64=8)
	UINT num4;			// size:4
};
