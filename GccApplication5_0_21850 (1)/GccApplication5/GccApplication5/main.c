#include<avr/io.h>
#include<avr/interrupt.h> //interrupt를 사용해야하므로 인터럽트 헤더파일을 포함시킨 것

#define sbi(PORTX,BitX) PORTX|=(1<<BitX)
#define cbi(PORTX,BitX) PORTX&=~(1<<BitX)

SIGNAL(INT0_vect) //INT0이 입력을 받았을 때
{
	cli(); //SREG의 7번비트 클리어
	PORTA=0xf0; //PA4~7까지만 LED를 켠다.
	sei(); //SREG=0x08;과 같은 의미로 외부 인터럽트 레지스터의 사용 시에 꼭 설정해주어야 한다.
}

SIGNAL(INT1_vect) //INT1이 입력을 받았을 때
{
	cli();
	PORTA=0x0f; //PA0~3까지만 LED를 켠다.
	sei();
}

int main()
{
	DDRA=0xff; //PA0~7을 입력으로 사용
	PORTA=0x00; //PA0~7에 0V를 출력
	DDRD=0x00; //PD0~1에 Switch가 연결되어 있음. 따라서 입력으로 이용
	sei(); //External interrupt를 사용하기 위해 꼭 필요한 소스

	EICRA=(1<<ISC01)|(1<<ISC00)|(1<<ISC11)|(1<<ISC10);
	//외부 인터럽트 제어 레지스터A로 INT0~3까지의 트리거 방식을 각자 두 비트씩으로 표현할 수 있음.
	EIMSK=(1<<INT1)|(1<<INT0);
	//외부 인터럽트 마스크 레지스터로 INT0~7을 enable하게 할지 말지를 선택하도록 함

	DDRB = 0xff;  //PWM을 모터부분이니까 출력으로 사용한다.
	DDRC = 0xff;  //Motor_DIrection 부분이니까 출력으로 사용한다.
	PORTC = 0x0a; //정방향
	PORTB = 0xff; //모두 5V 출력

	TCCR1A = (1 << COM1A1) | (0 << COM1A0) | (1 << COM1B1) | (0 << COM1B0) | (0 << COM1C1) | (0 << COM1C0) | (1 << WGM11) | (0 << WGM10);  //14번 fast PWM모드
	TCCR1B = (1 << WGM13 ) | (1 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10);
	//TCCR1B : 타이머/카운터1 제어 레지스터 B로서  WGMn3, WGMn2, WGMn1, WGMn0을 설정함으로써 타이머/카운터1과 3의 동작모드를 선택할 수 있고 나머지 CS12, CS11, CS10을 가지고 분주비를 바꿀 수 있다.

	ICR1 = 800;  //TOP값의 설정

	while(1)
	{
		OCR1A = 400;  //바퀴 한 쪽의 속도
		OCR1B = 400;  //바퀴 다른 한 쪽의 속도
	}
	while(1); //무한루프

	return 0;
}



