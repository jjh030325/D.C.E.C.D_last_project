# D.C.E.C.D_last_project

컴퓨터공학과 창의설계 기말프로젝트 
------------------------------------------------------
1. 플레이어 정보는 순서가 정해져 있다   
	- ID, NAME, GENDER, AGE, HP, MP, COIN   
	- 위 순서로 데이터가 입력되므로 항목은 생략하고 데이터만 입력한다.   
	- 데이터는 문자열로 입력한다.   
	- "KMU_CS123","HONG",FEMALE("F"로 표시),"33","200","5","43210"   


 2. 아이템은 정해진 순서가 없지만 입력이 들어온 순서대로 디코딩했을 시 출력해야 한다.
	- 즉 아이템의 순서를 기억해야 한다.
	- 따라서 아이템은 기호를 사용한다.
	- A(BOMB):1, P(POTION):3, C(CURE):10, B(BOOK), S(SHIELD), I(CANNON)


3. Friend List는 플레이어와 돌일하게 구현한다.
	- Friend는 여러명이 있으므로 앞에 숫자(char)를 붙인다.


4. DESCRIPTION
	- 동적 할당 + 1차원 배열 사용

5. 코드 정리   
	- player: 플레이어 구조체   
	- initializePlayer: 플레이어를 초기화 하는 함수   
		- 플레이어를 초기화 하지 않고 인코딩을 하면 배열에 쓰래기 값들이 저장되어 초기화를 한다   
	- compress: Run-Length알고리즘을 사용하여 압축을 하는 알고리즘   
	- encodePlayerInfo: 실제 플레이어의 정보를 인코딩 하는 함수   
		- issue: 플레이어의 정보를 의도와 다르게 인코딩 한다   
	- decompress: 압축 해제 함수
	- decodePlayerInfo: 플레이어 정보 디코딩 함수
	- encodeMain, decodeMain함수는 인코딩과 디코딩을 분리하기 위해 만든 임시 메인 함수이다
	- issue: 압축 알고리즘을 알 수 없다. 인코딩과 디코딩이 우리의 의도와 다르게 구현 되어서 우리의 의도대로 작동하는 지, 압축은 되는 지, 변조를 확인 할 수 있는지 확인 할 수 없다


6. 참고 사이트
	https://miro.com/app/board/uXjVMBua0dU=/
	(계속 업데이트 예정, 스터디 카페에서도 업데이트 할 거임)

7. gpt한테 물어본스크립트
	플레이어의 정보를 인코딩, 디코딩 하는 프로그렘을 만들어야해, 변조 테스트를 위해 1바이트 씩 총 4개가 변조될거야, 인코딩 할 떄 파일을 압축해야 하는데 이것도 직접 짜야해
	플레이어의 정보와 친구리스트는 데이터의 순서가 정해져 있지만 아이템은 정해진 순서가 없이 들어온 순서대로 아이템이 저장되어야 되(아이템의 종류와 갯수도 일치)

	또 c언어로 구현되어야 하고 인코더와 디코더 각각 따로 구현되어야 해, encoded를 실행하는메인함수에서 test.txt파일이 매개변수로 들어오면 encoded_data가 생성되
	decoded를 실행하는메인함수에서 test.txt파일이 매개변수로 들어오면 encoded_data가 생성되
실행 환경은 putty에서 실행 될 거야

	라이브러리는 #include <stdio.h> #include <stdlib.h> #include <string.h>이거 3개만 써야하고 파일을 압축해서 인코딩 해야하는데 압축 알고리즘도 짜야되

	플레이어의 정보는 플레이어의 정보(ID, NAME, GENDER, AGE, HP, MP, COIN),  아이템(BOMB, POTION, BOOL, CURE, SHIELD, CANNON), 친구리스트(각 친구마다 ID, NAME, GENDER, AGE), DESCRIPTION(자기 소개글)로 구성되어 있어.

