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
	- 복원과 변조의 용이성을 위해 압축하지 않는다.  

5. 변조 체크 및 복원 방법
	- 가로합, 세로합, 높이합을 이용하여 복원한다.   
	- 압축 데이터를 3차원으로 정렬한다.   
	- 각 줄마다 문자들의 아스키 값을 계산하여 합한다.   
	- 아스키 데이터는 가로줄, 세로줄, 높이 총 3가지를 만든다.   
		(가로 배열과 세로 배열은 높이에 따라 배열의 크기가 다르므로 높이를 계산 후 동적 배열한다.)   
	- 압축 데이터와 아스키 데이터를 구분하는 방법은 정해진 특수기호 6개를 이용하여 구분한다.   
	- 파일에 데이터를 2번 쓴다.   
	- 아스키 데이터는 압축 데이터를 이용하여 배열의 크기(아스키 데이터의 크기)를 알아낸 후 데이터를 읽어온다.   
	- 디코더에서는 파일의 크기가 짝수이므로 바이트의 절반으로 구분하여 파일을 읽는다.
	- 2개를 비교해 변조된 4부분을 정확히 알아낸다.   
	- 변조가 된 부분을 정확히 알 수 있으므로 해당 4부분을 복원한다.  
	- 이를 통해 변조 체크와 복원을 한다

7. 파일 작성
	- 압축한 문자열은 char로 입력하고, 이후 아스키 데이터는 int형으로 입력한다.   
	- 압축 데이터와 아스키 데이터를 구분하는 방법은 정해진 특수기호 6개를 이용한다.   
	- 디코더에서 아스키 코드를 재구성 할때는 배열의 크기가 정해져 있으니 배열의 크기로 잘라서 재구성한다.   

8. encode.c     
	
9. decode.c   
	

10. 아스키 데이터는 High는 무조건 10*10이고, row_sum이 압축 데이터 / 10 을 반올림 한 것과 크기가 동일하다. 이를 이용해 cloumn을 구한다.
