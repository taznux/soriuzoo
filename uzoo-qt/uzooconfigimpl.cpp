#include "uzooconfigimpl.h"

#include <qspinbox.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qdir.h>
#include <qstring.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qcstring.h>
#include <qobject.h>
#include <qtextview.h>

#include <iostream.h>
#include <stdlib.h>
#define kor(x) QString::fromLocal8Bit(x)

UzooConfigImpl::UzooConfigImpl(QWidget*parent,const char*name,bool modal,
	int fl): UzooConfig(parent,name,modal,fl)
{
	versionLineEdit->setEnabled(false);
	passwdLineEdit->setEchoMode(QLineEdit::Password);
	connect(versionCheckBox,SIGNAL(toggled(bool)),
			this,SLOT(slotVersionEdited(bool)));

	infoString[0]	= kor("한클라이언트당 접속인원  :");
	infoString[1]	= kor("전체 접속인원            :");
	infoString[2]	= kor("사용자 포트              :");
	infoString[3]	= kor("최대 결과 갯수           :");
	infoString[4]	= kor("업로드 폴더              :");
	infoString[5]	= kor("다운로드 폴더            :");
	infoString[6]	= kor("플레이어                 :");
	infoString[7]	= kor("플레이어 가능            :");
	infoString[8]	= kor("플레이어 시작시간(초)    :");
	infoString[9]	= kor("사용자ID                 :");
	infoString[10]	= kor("비밀번호                 :");
	infoString[11]	= kor("자동접속                 :");
	infoString[12]	= kor("소리바다 버젼            :");

	loadFileInfo();
	updateDialog();
	initTextFile();
}
UzooConfigImpl::~UzooConfigImpl()
{
}
void
UzooConfigImpl::initTextFile()
{
	developerTextView->setText(kor(
	"soriuzoo developer list<br>"
	"Analysis/Design<br>"
	"<b>Chang,Hye-Shik</b> perky@users.sourceforge.net<br>"
	"Qt Developer<br>"
	"<b>Lee,Jae-il</b> <a href=""mailto://sonegy@hanmail.net"">sonegy@hanmail.net</a><br>"
	));
	
	
	licenseTextView->setText(kor(
	"<CENTER><h1>GNU General Public License</h1></CENTER>

    <HR>
    <BLOCKQUOTE><P>
    This is an unofficial translation of the GNU General Public License into Korean. It
    was not published by the Free Software Foundation, and does not legally state the
    distribution terms for software that uses the GNU GPL--only the original English text
    of the GNU GPL does that. However, I hope that this translation will help Korean
    speakers understand the GNU GPL better.
    </BLOCKQUOTE>
    <HR>

    <P>
    이 문서는 자유 소프트웨어 재단(Free Software Foundation)의 GNU General Public
    License를 한국어로 번역한 것이다.
    <P>
    이 문서는 GNU General Public License가 내포하고 있는 호혜적인 자유와 공유의 정신을
    보다 많은 사람들에게 알리기 위한 희망에서 작성되었지만 자유 소프트웨어 재단의
    공식 문서로 취급될 수는 없다. 이는 원래의 문서가 의도하고 있는 내용들이 왜곡되지
    않고 법률적으로 유효하기 위해서 선행되어야 할 양국의 현행 법률과 언어의 적합성
    여부에 대한 전문가들의 검토 작업에 많은 비용이 필요하기 때문이다. 따라서, 자유
    소프트웨어 재단은 오역이나 해석상의 난점으로 인해서 발생될 지 모를 분쟁의
    가능성을 미연에 방지하고 문서가 담고 있는 내용과 취지를 보다 많은 사람들에게
    홍보하려는 상반된 목적을 한국어 번역문을 공식적으로 승인하지 않음으로써
    양립시킬 수 있을 것이다.
    <P>
    자유 소프트웨어 재단은 GNU General Public License를 실무에 적용할 경우, 오직
    영문판 GNU General Public License에 의해서 만이 그 법률적 효력이 올바르게 발생될
    수 있음을 권고하고 있다. 이 번역문은 법률적 검토와 문서간의 동일성 여부에 대한
    검증을 거치지 않은 것이며 이로 인해서 야기될 수 있을 지도 모를 법률적인 문제에
    대해서 어떠한 형태의 보증도 하지 않는다.
    <P>
    Original Copy: <A HREF=""http://www.gnu.org/copyleft/gpl.html"">GNU General Public License</A> <BR>
    Korean Translator: 1998 Song Changhun 송창훈 <A HREF=""mailto:chsong@cyber.co.kr"">chsong@cyber.co.kr</A>
    <P>

    <hr>

    <h3>목 차</h3>

    <UL>
    <LI>GNU GENERAL PUBLIC LICENSE
      <UL>
      <LI>전 문(前 文)
      <LI>복제와 개작, 배포에 관한 조건과 규정
      <LI>GPL을 실무에 적용하는 방법
      </UL>
    </UL>

    <P>

    <hr>

    <h2>GNU GENERAL PUBLIC LICENSE</h2>

    <P>
    Version 2, June 1991

    <PRE>
    Copyright (C) 1989, 1991 <A HREF=""http://www.fsf.org"">Free Software Foundation</A>, Inc.
    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
    저작권과 사용 허가에 대한 본 사항이 명시되는 한,
    어떠한 정보 매체에 의한 본문의 전재나 발췌도 무상으로 허용된다.
    단, 원문에 대한 수정과 첨삭은 허용되지 않는다.
    </PRE>

    <h2>전 문</h2>

    소프트웨어에 대한 대부분의 라이센스는 해당 소프트웨어에 대한 수정과 공유의
    자유를 제한하려는 것을 그 목적으로 한다. 그러나, GNU General Public License는 자유
    소프트웨어에 대한 수정과 공유의 자유를 호혜적으로 보장하기 위해서 성립되었다.
    자유 소프트웨어 재단이 제공하는 대부분의 소프트웨어들은 GNU General Public
    License의 규정에 의해서 관리되고 있으며 별도의 관리 방법이 보다 효과적이라고
    판단되는 라이브러리 서브루틴(library subroutine)의 경우, 독립된 문서인 GNU Library
    General Public License를 선택적으로 적용하고 있다. 자유 소프트웨어란 이를
    사용하려는 모든 사람에 대해서 동일한 자유와 귄리가 함께 양도되는 소프트웨어를
    의미하며 프로그램 저작자의 의지에 따라 어떠한 프로그램에도 이 규정들이 적용될
    수 있다.
    <P>
    자유 소프트웨어를 언급할 때 사용되는 '자유'라는 단어의 의미는 금전적인 측면의
    자유가 아닌 구속되지 않는다는 관점에서의 자유를 의미하며 GNU General Public
    License는 자유 소프트웨어를 이용한 복제와 개작, 배포와 수익 사업 등의 가능한 모든
    형태의 자유를 실제적으로 보장한다. 여기에는 소스 코드의 전부 또는 일부를
    원용해서 개선된 프로그램으로 변형시키거나 새로운 프로그램을 창작할 수 있는
    자유가 포함되며 자신에게 양도된 이러한 자유와 권리들을 보다 명확하게 인식할 수
    있도록 하기 위한 규정 또한 포함되어 있다.
    <P>
    GNU General Public License는 이 문서에 소프트웨어 피양도자의 권리를 제한하는 특정
    조항과 단서들을 별항으로 첨가시키지 못하게 함으로써 사용자들의 실질적인 자유와
    권리를 보장하고 있다. 자유 소프트웨어의 개작과 배포에 관계하고 있는 사람들은
    이러한 무조건적인 권리 양도 규정을 준수해야만 한다.
    <P>
    예를 들면, 특정 프로그램을 배포할 경우 양도자는 피양도자에게 자신이 양도받았던
    모든 권리를 수익 여부에 관계없이 그대로 이전해야만 한다. 소스 코드에 대한 사용
    권리 또한 여기에 포함되어야 하며 이와 같은 사항들을 명시함으로써
    피양도자들에게 그들이 양도받은 권리를 알 수 있도록 해야 한다.
    <P>
    자유 소프트웨어 재단은 다음과 같은 두 가지 방법에 의해서 반복되는 양도에 따른
    사용자 모두의 권리를 보호한다: (1) 저작권을 인정함으로써 프로그램 저작자들의
    권리를 보호한다. (2) 저작권의 양도에 관한 실정법에 의해서 유효한 법률적 효력을
    갖는 GNU General Public License를 통해서 소프트웨어의 복제와 개작, 배포 등에 대한
    소프트웨어 피양도자의 권리를 실질적으로 보장한다.
    <P>
    자유 소프트웨어의 사용자들은 지속적인 양도 과정을 통해서 소프트웨어 자체에
    수정과 변형에 의한 문제가 발생될 수 있으며 이는 최초의 저작자에 의한
    소프트웨어가 갖는 문제가 아닐 수 있다는 개연성에 대해서 인식하고 있어야 한다.
    GNU General Public License에 자유 소프트웨어에 대한 어떠한 형태의 보증도 규정하지
    않은 이유는 이러한 점들이 고려되었기 때문이며 이는 프로그램 원저작자와 자유
    소프트웨어 재단의 자유로운 활동을 보장하는 현실적인 수단이기도 하다.
    <P>
    특허 제도는 자유 소프트웨어의 발전을 위협하는 요소일 수밖에 없다. 따라서, 자유
    소프트웨어를 배포할 경우 개별적인 배포 과정에 특허를 취득한 저작물을 함께
    포함시키지 않음으로써 이용 상의 자유가 제한되지 않도록 하는 것이 최선의
    방법이다. GNU General Public License는 이러한 문제에 대처하기 위해서 특허가 취득된
    저작물은 그 라이센스를 불특정 다수(이하, &quot;공중&quot;이라 한다)에게 공개적으로
    허용하는 경우에 한해서 자유 소프트웨어와 함께 사용할 수 있도록 규정하고 있다.
    <P>
    복제(copying)와 개작(modification), 배포(distribution) 등에 관련된 구체적인 조건과
    규정은 다음과 같다.
    <P>

    <h2>복제와 개작, 배포에 관한 조건과 규정</h2>

    <P>
    <strong>제 0 항.</strong>
    본 라이센스는 GNU General Public License의 규정에 따라서 배포될 수 있다는
    사항이 저작권자에 의해서 명시된 모든 컴퓨터 프로그램 저작물에 대해서 동일하게
    적용된다. 컴퓨터 프로그램 저작물(이하, &quot;프로그램&quot;이라 한다)이란 특정
    프로그램이나 이와 관련된 기타 저작물을 의미하고 &quot;2차적 프로그램&quot;이란
    저작권법의 규정에 따라 프로그램의 전부 또는 상당 부분을 원용하거나 다른
    프로그래밍 언어로의 번역을 포함할 수 있는 개작 과정을 통해서 창작된 새로운
    프로그램과 이와 관련된 저작물을 의미한다(이후로 다른 프로그래밍 언어로의
    번역은 별다른 제한 없이 개작의 범위에 포함되는 것으로 간주한다) &quot;피양도자&quot;란
    GNU General Public License의 규정에 의해서 프로그램을 양도받은 사람을 의미한다.
    <P>
    본 라이센스는 프로그램에 대한 복제와 개작, 배포 행위에 대해서만 적용된다.
    따라서, 프로그램을 실행시키는 행위는 제한되지 않으며 프로그램의 실행에 따른
    결과물은 실행 자체에 의한 결과물의 생성 여부에 상관없이 결과물이 2차적
    프로그램을 구성했을 때에 한해서 본 라이센스의 규정을 적용할 수 있다. 2차적
    프로그램의 구성 여부는 2차적 프로그램 안에서의 프로그램의 역할을 토대로
    판단한다.
    <P>
    <strong>제 1 항.</strong>
    피양도자는 프로그램에 대한 보증을 제공하지 않는다는 사실과 저작권을
    함께 명시하는 한, 양도받은 소스 코드의 전부 또는 일부를 어떠한 정보 매체를
    통해서도 복제해서 배포할 수 있다. 피양도자가 프로그램의 소스 코드를 재배포할
    때는 프로그램에 대한 보증이 결여되어 있다는 사실과 본 라이센스에 대해서 언급한
    사항들을 양도받은 그대로 유지시켜야 하며 GNU General Public License 원문을 함께
    제공해야 한다.
    <P>
    복제물을 배포할 경우, 복제물을 제작하기 위해서 소요된 경비를 충당하기 위해서
    배포본을 유료로 판매할 수 있으며 유료 판매에 따른 배포본의 환불을 보장하는
    별도의 보증을 설정할 수 있다.
    <P>
    <strong>제 2 항.</strong>
    피양도자는 자신이 양도받은 프로그램의 전부 또는 일부를 개작할 수 있으며
    이를 통해서 2차적 프로그램을 창작할 수 있다. 개작된 프로그램이나 창작된 2차적
    프로그램의 소스 코드는 제 1 항의 규정에 의해서 다음의 사항들을 만족시키는
    조건에 한해서 복제해서 배포될 수 있다.

    <OL TYPE=""a"">
    <LI>
      개작된 파일은 파일이 개작된 사실과 개작된 날짜가 명시적으로 확인될 수
      있도록 작성되어야 한다.<P>
    <LI>
      배포하거나 출판하려는 저작물의 전부 또는 일부가 양도받은 프로그램으
      로부터 파생된 것이라면 개작된 프로그램에 대한 배포본이나 출판물 전 체에
      대한 사용 권리를 공중에게 무상으로 허용해야 한다.<P>
    <LI>
      개작된 프로그램의 일반적인 실행 형태가 명령어 입력 방식에 의한 대화 형
      구조 일 경우, 개작된 프로그램은 이러한 대화형 구조로 평이하게 실 행되었을
      때 저작권에 대한 사항과 프로그램에 대한 보증이 결여되어 있 다는 사실이
      개작된 프로그램을 본 라이센스의 규정에 의해서 다시 개작 해서 배포할 수
      있다는 사항과 GNU General Public License를 열람할 수 있는 방법과 함께 실행
      직후에 지면 또는 화면을 통해서 출력될 수 있도 록 작성되어야 한다(예외 규정:
      양도받은 프로그램이 대화형 구조를 갖 추고 있다 하더라도 통상적인 실행
      환경에서 전술한 사항들이 출력되지 않는 형태였을 경우, 이를 개작한 프로그램
      역시 관련 사항들을 출력시 키지 않아도 된다)<P>
    </OL>

    <P>
    본 조항들은 개작된 부분이 포함된 2차적 프로그램 전체에 적용된다. 만약, 어떠한
    저작물이 2차적 프로그램에 포함되어 있는 부분과 동일한 것이라 하더라도 그것이
    양도받은 프로그램으로부터 파생된 것이 아니라 별도의 독립 저작물로 인정될 만한
    상당한 이유가 있을 경우, 이 저작물의 개별적인 배포 과정에는 본 라이센스와
    규정들이 적용되지 않는다. 그러나, 이러한 저작물이 2차적 프로그램에 포함되어
    함께 배포된다면 개별적인 저작권과 배포 기준에 상관없이 배포본의 전체 저작물
    모두가 본 라이센스에 의해서 관리되어야 하며 전체 저작물의 일부 또는 전부에 대한
    사용상의 모든 권리가 공중에게 무상으로 양도되어야 한다.
    <P>
    이러한 규정은 개별적인 저작물에 대한 저작권자의 권리를 말소시키려는 것이
    아니라 2 차적 프로그램으로부터 반복적으로 파생되거나 이러한 프로그램들을 모아
    놓은 배포본에 대해서 본 라이센스의 규정들을 동일하게 적용하기 위한 것이다.
    <P>
    프로그램(또는 2차적 프로그램)들을 단순히 저장하거나 배포할 목적으로 함께
    구성해 놓은 경우는 이들이 파생적 저작물을 생성하지 않는 한 본 라이센스에 의해서
    관리된다.
    <P>
    <strong>제 3 항.</strong> 피양도자는 다음의 조항 중 하나를 만족시키는 조건에 한해서 제 1 항과 제 2
    항의 규정에 따라 프로그램(또는 제 2 항의 규정에 의한 2 차적 프로그램)을 목적
    코드나 실행 형태로 복제해서 배포할 수 있다.

    <OL TYPE=""a"">
    <LI>
      목적 코드나 실행 형태에 해당하는 소스 코드의 전부를 제 1 항과 제 2 항의
      규정에 따라서 컴퓨터가 입력받거나 번역할 수 있는 형태로 소프트 웨어의
      배포를 위해서 일반적으로 사용되는 정보 매체를 통해서 함께 제 공해야 한다.<P>
    <LI>
      목적 코드나 실행 형태에 해당하는 소스 코드의 전부를 최소한 3년 이상
      유지될 수 있는 인쇄물의 형태로 제 1 항과 제 2 항의 규정에 따라서
      소프트웨어의 배포를 위해서 일반적으로 사용되는 정보 매체를 통해서 제작
      실비에 준하는 비용만을 부과해서 공중에게 양도될 수 있도록 함께 제공해야
      한다.<P>
    <LI>
      목적 코드나 실행 형태에 해당하는 소스 코드의 전부를 취득할 수 있는
      방법에 대한 정보를 함께 제공해야 한다(이 항목은 비영리적인 배포와 항목
      2)에 의해서 목적 코드나 실행 형태의 배포본을 제공할 때에 한해 서 적용될 수
      있다)
    </OL>

    <P>
    저작물에 대한 소스 코드란 해당 저작물을 개작하기 위해서 일반적으로 선호되는
    표현 형식을 의미하고 실행물에 대한 소스 코드란 올바르게 실행되기 위해서 필요한
    모듈과 인터페이스 정의 파일, 컴파일과 설치를 위해서 필요한 스크립트 등을 모두
    포함한다. 그러나, 컴파일러나 커널과 같은 운영체제의 주요 부분들에 대한 소스
    코드나 바이너리 형태는 프로그램이 이러한 부분들과 직접 관계되지 않는 한 함께
    제공하지 않아도 무관하다.
    <P>
    목적 코드나 실행 형태를 특정 장소로부터 복제할 수 있도록 허용하는 방식으로
    배포할 경우, 동일한 장소로부터 소스 코드를 복제할 수 있도록 허용하는 것은
    피양도자에게 소스 코드를 목적 코드나 실행 형태와 함께 복제해 갈 것을 규정하지
    않았다 하더라도 소스 코드를 함께 배포하는 것으로 간주한다.
    <P>
    <strong>제 4 항.</strong> 본 라이센스에 의해서 명시적으로 프로그램을 양도받지 않았다면 양도받은
    프로그램에 대한 복제와 개작, 별도의 라이센스 설정과 배포 행위 등을 할 수 없다.
    이와 관련된 어떠한 행위도 법률적으로 무효이며 본 라이센스에서 규정하고 있는
    사용상의 모든 권리는 자동적으로 소멸된다. 단, 본 라이센스의 규정에 의하지 않고
    양도받은 프로그램이라 하더라도 이를 명시적인 라이센스 양도 규정에 따라 다시
    배포했을 경우, 프로그램을 다시 양도받은 제 3의 피양도자는 본 라이센스를
    준수하는 조건하에서 사용상의 권리를 유지할 수 있다.
    <P>
    <strong>제 5 항.</strong> 피양도자는 프로그램의 양도에 관한 본 라이센스에 서명하지 않음으로써 본
    라이센스의 규정들을 받아들이지 않을 수 있다. 이 경우, 피양도자에게는 프로그램에
    대한 단순한 사용만이 허용되며 프로그램과 2차적 프로그램에 대한 개작과 배포
    행위는 허용되지 않는다. 이는 피양도자가 라이센스에 서명하지 않음으로써 발생된
    법률적 금지 사항이다. 따라서, 프로그램(또는 2차적 프로그램)을 개작하거나
    배포하는 행위는 복제와 개작, 배포에 관한 본 라이센스의 규정과 조건들을 모두
    받아들이겠다는 묵시적인 동의로 간주한다.
    <P>
    <strong>제 6 항.</strong> 피양도자에 의해서 프로그램(또는 2차적 프로그램)이 반복적으로 배포될
    경우, 각 단계에서의 피양도자는 본 라이센스의 규정에 의한 프로그램의 복제와 개작,
    배포에 대한 권한을 최초의 프로그램 양도자로부터 양도받은 것으로 자동적으로
    간주된다. 프로그램(또는 2차적 프로그램)을 양도할 때는 피양도자의 권리를 제한할
    수 있는 어떠한 사항도 별항으로 첨가할 수 없으며 그 누구도 본 라이센스의 규정들을
    준수하도록 강제할 수 없다.
    <P>
    <strong>제 7 항.</strong> 법원의 판결이나 특허권 침해에 대한 주장 또는 특허 문제에 국한되지 않는
    그 밖의 다른 이유들로 인해서 본 라이센스의 규정에 배치되는 사안이 발생한다
    하더라도 본 라이센스에 배치되는 규정들이 본 라이센스에 대한 실행 상의 우선권을
    갖게 되지는 않는다. 따라서, 법원의 명령이나 합의 등에 의해서 본 라이센스에
    위배되는 사항들이 부과된다 하더라도 본 라이센스의 규정들을 함께 충족시키면서
    해당 프로그램을 배포할 수 없다면 이 프로그램의 배포는 금지된다. 예를 들면, 특정
    특허 관련 라이센스가 직접 또는 간접적인 양도 방법에 의해서 프로그램을 무상으로
    배포하는 것을 허용하지 않는다면 이 프로그램은 본 라이센스의 규정에 의해서
    관리되는 프로그램들과 함께 배포될 수 없다.
    <P>
    특정 상황에서 본 조항의 일부분이 적용될 수 없는 경우에는 해당 부분을 제외한
    나머지 부분들을 적용시키며 본 조항의 전부를 적용시키기 위해서는 다른 상황과
    조건들이 필요하다.
    <P>
    본 조항의 목적은 특허나 재산권 침해 등의 행위를 조장하거나 해당 권리를 인정하지
    않으려는 것이 아니라 GNU General Public License의 실제적인 적용을 통해서 자유
    소프트웨어의 배포 체계를 통합적으로 보호하기 위한 것이다. 많은 사람들이 배포
    체계에 대한 신뢰있는 지원을 계속해 줌으로써 소프트웨어의 다양한 분야에 많은
    공헌을 해 주었다. 소프트웨어를 어떠한 배포 체계를 통해서 배포할 것인가를
    결정하는 것은 전적으로 저작자와 기증가들의 의지에 달려있지 일반 사용자들이
    강요할 수 있는 문제는 아닌 것이다.
    <P>
    본 조항은 계속되는 본 라이센스의 내용들을 통해서 중요하게 취급되고 있는 점들을
    보다 명확하게 설명하는 데 도움이 될 것이다.
    <P>
    <strong>제 8 항.</strong> 특허권과 저작권의 법적 처리 방식에 의해서 특정 국가에서 프로그램의
    배포와 사용이 함께 또는 개별적으로 금지될 경우, 본 라이센스에 의해서 프로그램을
    공개한 원저작자는 문제가 발생되지 않는 국가에 한해서 이를 배포한다는 배포상의
    지역적 제한 조건을 설정할 수 있으며 이러한 사항은 본 라이센스의 일부로 간주된다.
    <P>
    <strong>제 9 항.</strong> 자유 소프트웨어 재단은 GNU General Public License를 개정하거나 갱신할 수
    있다. 개정되거나 변동되는 사항은 새로운 문제와 관심에 따라서 세부적으로
    조정되겠지만 그 근본 정신은 바뀌지 않을 것이다.
    <P>
    GNU General Public License의 모든 버전은 다른 버전 번호로 구별될 것이다. 양도받은
    프로그램이 특정 버전의 라이센스를 명시하고 있다면 해당 버전 또는 그 이후의
    라이센스가 적용되며 버전을 명시하지 않은 경우는 어떠한 버전의 라이센스를
    적용해도 무방하다.
    <P>
    <strong>제 10 항.</strong> 프로그램의 일부를 본 라이센스와 배포 기준이 다른 자유 프로그램과 함께
    배포할 경우, 해당 프로그램의 저작자로부터 서면을 통한 승인을 받아야 한다. 자유
    소프트웨어 재단이 저작권을 갖고 있는 소프트웨어를 사용하기 위해서는 자유
    소프트웨어 재단의 승인을 얻어야 한다. 자유 소프트웨어 재단은 승인 요건에 대해서
    예외 규정을 둘 수 있다. 자유 소프트웨어 재단은 자유 소프트웨어의 2차적
    저작물들을 모두 자유로운 상태로 유지시키려는 목적과 소프트웨어의 일반적인
    공유와 재활용을 증진시키려는 기준에 근거해서 승인 여부를 결정할 것이다.
    <P>
    <strong>보증의 결여</strong>
    <P>
    <strong>제 11 항.</strong> 본 라이센스에 의한 프로그램은 무상으로 양도되므로 관련 법이 허용하는
    한도 내에서 어떠한 형태의 보증도 제공하지 않는다. 단, 프로그램의 저작권자와 제
    3의 배포자에 의해서 공동 또는 개별적으로 특정 목적에 대한 프로그램의 적합성
    여부를 검증하기 위한 경우나 상업적 판매에 따른 별도의 보증이 제공된다는 사항이
    서면으로 명시되어 있는 경우는 예외로 한다. 이 경우도 해당 프로그램 자체가 갖고
    있는 근원적인 보증의 결여를 제한할 수는 없다. 프로그램과 프로그램의 실행에 따라
    발생할 수 있는 위험은 모두 피양도자에게 인수되며 이에 따른 보수 및 복구를 위한
    제반 경비 또한 모두 피양도자가 부담한다.
    <P>
    <strong>제 12 항.</strong> 저작권자나 제 3의 배포자가 프로그램의 손상 가능성을 사전에 알고 있었다
    하더라도 발생된 손실이 관련 법규에 의해서 보호되고 있거나 저작권자나 프로그램
    자체에 대한 보증을 제공하지 않는다는 전제로 프로그램과 개작된 프로그램을 함께
    또는 개별적으로 공급한 배포자가 서면으로 별도의 보증을 설정한 경우가 아니라면
    프로그램의 사용이나 사용상의 미숙으로 인해서 발생된 손실은 모두 피양도자의
    책임이다. 발생된 손실의 일반성이나 특수성 뿐만 아니라 원인의 우발성 및 필연성도
    고려되지 않는다.

    <h3>복제와 개작, 배포에 관한 조건과 규정의 끝.</h3>

    <h2>규정들을 실무에 적용하는 방법</h2>

    <P>
    개발한 프로그램이 보다 많은 사람들에게 유용하게 사용되기를 원한다면 그
    프로그램이 본 라이센스의 규정에 따라서 자유롭게 수정되고 배포될 수 있도록 자유
    소프트웨어로 만드는 것이 최선의 방법이다.
    <P>
    다음과 같은 사항들을 프로그램에 첨가함으로써 해당 프로그램을 자유 소프트웨어로
    만들 수 있다. 프로그램에 대한 보증을 제공하지 않는다는 사실을 가장 효과적으로
    전달할 수 있는 방법은 소스 코드가 포함되어 있는 모든 파일의 시작 부분에 이러한
    사항들을 명시하는 것이다. 각각의 파일들은 최소한 저작권과 GPL을 취득할 수 있는
    방법을 명시해야만 한다.

    <PRE>
    <var>
    프로그램의 이름과 용도에 대한 설명을 위해서 한 줄을 사용한다.
    </var>
    Copyright (C) 19<var>yy</var>  <var>프로그램 저작자의 이름</var>
    이 프로그램은 자유 소프트웨어이다. 소프트웨어의 피양도자는
    자유 소프트웨어  재단의 GNU General Public License의 규정에
    의해서 이 프로그램을 개작된 2차적 프로그램과 함께 또는 개별적으로
    배포할 수 있다.
    이 프로그램은 보다 유용하게 사용될 수 있으라는 희망에서
    배포되고 있지만 제품에 대한 어떠한 형태의 보증도 하지 않는다.
    보다 자세한 사항에 대해서는 GNU General Public  License를
    참고하기 바란다.
    GNU General Public License는 이 프로그램과 함께 제공된다.
    만약, 이 문서가 누락되어 있다면 자유 소프트웨어 재단에 문의하기
    바란다(자유 소프트웨어 재단: Free  Software Foundation, Inc.,
    59 Temple Place - Suite 330, Boston, MA 02111-1307, USA)
    </PRE>

    또한, 프로그램 저작자와 서면 또는 전자 메일을 통해서 연락할 수 있는 정보를
    기재해야 한다.
    <P>
    만약, 이 프로그램이 명령어 입력 방식에 의한 대화형 구조를 택하고 있다면
    프로그램이 대화형 방식으로 실행되는 초기 상태에서 다음과 같은 주의 사항을
    출력시켜야 한다.

    <Pre>
    Gnomovision version 69, Copyright (C) 19<var>yy프로그램 저작자의 이름</var>
    Gnomovision은 제품에 대한 어떠한 형태의 보증도 제공되지 않는다.
    보다 자세한 사항은 'show w' 명령어를 이용해서 관련된 사항을
    출력해 보기 바란다. 본 프로그램은 자유 소프트웨어이며 특정 규정들을
    만족시키는 조건하에서 재배포될 수 있다. 배포에 대한 해당 규정은
    'show c' 명령어를 통해서 참조할 수 있다.
    </PRE>

    <P>
    <samp>'show w'</samp>와 <samp>'show c'</samp>는 General Public License의 해당 부분을 참조하기 위한 가상의
    명령어이다. 따라서, 이 명령어들은 마우스를 이용하거나 메뉴 방식을 구성하는 등의
    프로그램에 적합한 여러 가지 형태으로 변형될 수 있을 것이다.
    <P>
    만약, 프로그램 저작자가 학교나 기업과 같은 단체나 기관에 고용되어 있다면
    프로그램의 자유로운 배포를 위해서 고용주나 해당 기관장으로 부터 프로그램에
    대한 저작권을 포기한다는 동의를 얻어야 한다. 예를 들면, 다음과 같은 형식이 될 수
    있다.

    <PRE>
    본사는 James Hacker에 의해서 작성된
    'Gnomovision' 프로그램에 관계된
    모든 저작권을 포기한다.
    1989년 4월 1일
    Yoyodye, Inc., 부사장: Ty Coon
    서명: <var> Ty Coon의 서명</var>
    </PRE>

    <P>
    본 라이센스는 자유 소프트웨어로 설정된 프로그램을 독점 소프트웨어와 함께
    사용하는 것을 허용하지 않는다. 만약, 작성된 프로그램이 라이브러리 서브루틴과
    같은 프로그램일 경우에는 이를 독점 소프트웨어 형태의 응용 프로그램과 함께
    사용함으로써 보다 효과적으로 활용될 수 있다고 생각할 수도 있을 것이다. 이러한
    경우는 본 라이센스 대신에 GNU Library General Public License를 사용함으로써 소기의
    목적을 충족시킬 수 있을 것이다."));
}
void
UzooConfigImpl::saveFileInfo()
{
	info.biggestClient	= myserver1SpinBox->text().toShort();
	info.biggestEvery 	= myserver2SpinBox->text().toShort();
	info.userPort		= userportSpinBox->text().toShort();
	info.biggestSearch	= searchSpinBox->text().toShort();
	
	info.uploadPath = "";
	for(int i=0 ; i <(int)upFolderComboBox->count() ; i++){
		info.uploadPath.append( upFolderComboBox->text(i)+QString("\n")) ;
	}
	info.downloadPath	= downFolderLineEdit->text();
	info.defaultPlayerPath= playerLineEdit->text();
	if (startPlayerCheckBox->isChecked() == true)
		info.playerEnable = "true";
	else if (startPlayerCheckBox->isChecked() == false)
		info.playerEnable = "false";
	info.playerStartTime= laterPlayerSpinBox->text().toShort();
	
	info.userid = useridLineEdit->text();
	info.passwd = passwdLineEdit->text();
	if ( autoLoginCheckBox->isChecked() == true)
	{
		info.autoLogin = "true";
	}else
	{
		info.autoLogin = "false";
	}
	info.version		= versionLineEdit->text();

	// 파일을 열고 저장한다.
	QFile infoFile(kor( QDir::homeDirPath() + "/.uzoo-qt" ));
	infoFile.remove();
	if(infoFile.open(IO_WriteOnly))
	{
		QTextStream ts(&infoFile);
		ts << infoString[0] << QString::number(info.biggestClient) << "\n";
		ts << infoString[1] << QString::number(info.biggestEvery) << "\n";
		ts << infoString[2] << QString::number(info.userPort) << "\n";
		ts << infoString[3] << QString::number(info.biggestSearch) << "\n";
		ts << infoString[4] << info.uploadPath << "\n";
		ts << infoString[5] << info.downloadPath << "\n";
		ts << infoString[6] << info.defaultPlayerPath << "\n";
		ts << infoString[7] << info.playerEnable << "\n";
		ts << infoString[8] << QString::number(info.playerStartTime)<<"\n";
		ts << infoString[9] << info.userid << "\n";
		ts << infoString[10] << info.passwd << "\n";
		ts << infoString[11] << info.autoLogin << "\n";
		ts << infoString[12] << info.version  <<"\n";
	}
	infoFile.close();

	emit sendInfo( info );
}
void
UzooConfigImpl::updateDialog()
{
	// 설정내용을 Dialog에 올린다.
	myserver1SpinBox->setValue( info.biggestClient);
	myserver2SpinBox->setValue( info.biggestEvery);
	userportSpinBox->setValue( info.userPort);
	searchSpinBox->setValue(info.biggestSearch);
	//upLoadPath
	downFolderLineEdit->setText(kor(info.downloadPath) );
	playerLineEdit->setText(kor( info.defaultPlayerPath) );

	if (info.playerEnable.lower() == "true")
		startPlayerCheckBox->setChecked(true);
	else if (info.playerEnable.lower() == "false")
		startPlayerCheckBox->setChecked(false);
	
	laterPlayerSpinBox->setValue(info.playerStartTime);
	useridLineEdit->setText(kor(info.userid));
	passwdLineEdit->setText(kor(info.passwd));

	if (info.autoLogin.lower() == "true")
		autoLoginCheckBox->setChecked(true);	
	else if (info.autoLogin.lower() == "false")
		autoLoginCheckBox->setChecked(false);

	versionLineEdit->setText(info.version);
}
/*
 * 설정파일에서 정보를 꺼내온다. 없다면 기본정보를 넣어준다.
 * 이후 GUI에 이 정보를 업데이트한다.
 */
void
UzooConfigImpl::loadFileInfo()
{
	// 파일을 열고 정보를 얻어와 다양한 데이타에 저장을 한다.
	// 지정된 장소에 설정파일을 열고, 형식을 읽는다.
	// 물론 없다면 만들지~~
	QFile infoFile(kor( QDir::homeDirPath() + "/.uzoo-qt" ));
	if( !infoFile.exists()) // 존재하지 않는다면
	{	// default로 설정내용을 저장한다.
		if(infoFile.open(IO_WriteOnly))
		{
			QTextStream ts(&infoFile);
			ts << infoString[0] << kor("1") << "\n";
			ts << infoString[1] << kor("3") << "\n";
			ts << infoString[2] << kor("9001") << "\n";
			ts << infoString[3] << kor("500") << "\n";
			ts << infoString[4] << "\n";
			ts << infoString[5] << QDir::homeDirPath()<<"\n";
			ts << infoString[6] << kor("xmms") << "\n";
			ts << infoString[7] << kor("true") << "\n";
			ts << infoString[8] << kor("5") << "\n";
			ts << infoString[9] << "\n";
			ts << infoString[10] << "\n";
			ts << infoString[11] << kor("false") <<"\n";
			ts << infoString[12] << kor("1.94") << "\n";
		}
		infoFile.close();
	}
	// 파일에서 설정을 불러온다.
	if(infoFile.open(IO_ReadOnly))
	{
		QTextStream ts(&infoFile);
		int infoSize = 13;
		for(int i=0 ; i < infoSize ; i++)
		{
			QString line = ts.readLine().local8Bit();
			//cout << line.latin1() << endl;
			int findIndex = line.find(":") + 1;
			int findLen = line.length() - findIndex;
			if 
			(qstrcmp(line.left(infoString[0].local8Bit().length()).latin1()
				, infoString[0].local8Bit().data()) == 0)
			{
				info.biggestClient = line.right(findLen).toShort(); 
			}
			else if 
			(qstrcmp(line.left(infoString[1].local8Bit().length()).latin1()
				, infoString[1].local8Bit().data()) == 0)
			{
				info.biggestEvery = line.right(findLen).toShort();
			}
			else if 
			(qstrcmp(line.left(infoString[2].local8Bit().length()).latin1()
				, infoString[2].local8Bit().data()) == 0)
			{
				info.userPort = line.right(findLen).toShort();
			}
			else if 
			(qstrcmp(line.left(infoString[3].local8Bit().length()).latin1()
				, infoString[3].local8Bit().data()) == 0)
			{
				info.biggestSearch = line.right(findLen).toShort();
			}
			else if 
			(qstrcmp(line.left(infoString[4].local8Bit().length()).latin1()
				, infoString[4].local8Bit().data()) == 0)
			{
				info.uploadPath = line.right(findLen);
			}
			else if 
			(qstrcmp(line.left(infoString[5].local8Bit().length()).latin1()
				, infoString[5].local8Bit().data()) == 0)
			{
				info.downloadPath = line.right(findLen);
			}
			else if 
			(qstrcmp(line.left(infoString[6].local8Bit().length()).latin1()
				, infoString[6].local8Bit().data()) == 0)
			{
				info.defaultPlayerPath = line.right(findLen);
			}
			else if 
			(qstrcmp(line.left(infoString[7].local8Bit().length()).latin1()
				, infoString[7].local8Bit().data()) == 0)
			{
				info.playerEnable = line.right(findLen);
			}
			else if 
			(qstrcmp(line.left(infoString[8].local8Bit().length()).latin1()
				, infoString[8].local8Bit().data()) == 0)
			{
				info.playerStartTime = line.right(findLen).toShort();
			}
			else if
			(qstrcmp(line.left(infoString[9].local8Bit().length()).latin1()
					,infoString[9].local8Bit().data()) == 0)
			{
				info.userid = line.right(findLen);	
			}
			else if
			(qstrcmp(line.left(infoString[10].local8Bit().length()).latin1()
					,infoString[10].local8Bit().data()) == 0)
			{
				info.passwd = line.right(findLen);
			}
			else if
			(qstrcmp(line.left(infoString[11].local8Bit().length()).latin1()
					,infoString[11].local8Bit().data()) == 0)
			{
				info.autoLogin = line.right(findLen);
			}
			else if
			(qstrcmp(line.left(infoString[12].local8Bit().length()).latin1()
					,infoString[12].local8Bit().data()) == 0)
			{
				info.version = line.right(findLen);
			}
		}
	}
	infoFile.close();
}
/*
 * slot
 */
void
UzooConfigImpl::slotApply()
{
	saveFileInfo();
}
void
UzooConfigImpl::slotOk()
{
	saveFileInfo();
	this->hide();
}
void
UzooConfigImpl::slotCancel()
{
	this->hide();
}
void
UzooConfigImpl::slotVersionEdited(bool b)
{
	versionLineEdit->setEnabled(b);
}
void
UzooConfigImpl::slotHelpBrowser()
{
	int value = system("konqueror http://sonegy.home.uos.ac.kr/soriuzoo&");
	cout << "Return browser:"<< value << endl;
}
void
UzooConfigImpl::slotFindPlayer()
{
}
void
UzooConfigImpl::slotDownLoadFolder()
{
}


