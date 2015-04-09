--TEST--
Test for unidecode
--FILE--
<?php
$test = array(
"νɨɑииєγ",
"VĪÂИИЄ￥",
"√¡ä₪₪عγ",
"ƔĩΛהה£¥",
"€ЄÖ×Ø",
"12345",
"影師嗎",
"C'est déjà l'été.",
"Nín hǎo. Wǒ shì zhōng guó rén",
"Компьютер",
"jaja---lol-méméméoo--a",
"dollar $ euro € livre £ Ÿ Ë | Ó Ê ª Z ı ñ",
"___This is a test ---",
"1 2 3",
"über",
"ộ, ủ, ĩ, ệ",
"one two three four five\n\t",
'大平矿难死者增至66人', '郑煤所属煤矿全停产エンタープライズ検索プラットフォーム',
'don Quijote 에 오신것을 환영합니다!

손님이 스페인과 라틴아메리카의 그어느학교를 선택하여 학습하든지 손님은 한단락의
보귀한 경력을 얻게 될것이다. 우리는 손님이 요구에 따라 손님이 스페인이거나
라틴아메리카주의 학습과정을 안배하여 줄것이다. don Quijote의 유일한 목표는 바로
품질을 보증하는데 있다. 우리들로 하여금 자랑스럽게 생각하는 것은 우리의 새로운
학원의 50%가 기존학원들이 추천한 것이라는 것이다 ',
'Vr sa god');

foreach ($test as $t) {
	echo ">>".unidecode($t)."<<\n";
}

?>
--EXPECT--
>>niaiiieg<<
>>VIAIIIeY=<<
>>[?]!aNSNS`g<<
>>GiLhhPSY=<<
>>EURIeOxO<<
>>12345<<
>>Ying Shi Ma <<
>>C'est deja l'ete.<<
>>Nin hao. Wo shi zhong guo ren<<
>>Komp'iuter<<
>>jaja---lol-mememeoo--a<<
>>dollar $ euro EUR livre PS Y E | O E a Z i n<<
>>___This is a test ---<<
>>1 2 3<<
>>uber<<
>>o, u, i, e<<
>>one two three four five
	<<
>>Da Ping Kuang Nan Si Zhe Zeng Zhi 66Ren <<
>>Zheng Mei Suo Shu Mei Kuang Quan Ting Chan entapuraizuJian Suo puratsutohuomu<<
>>don Quijote e osingeoseul hwanyeonghabnida!

sonnimi seupeingwa ratinamerikayi geueoneuhaggyoreul seontaeghayeo hagseubhadeunji sonnimeun handanragyi
bogwihan gyeongryeogeul eodge doelgeosida. urineun sonnimi yogue ddara sonnimi seupeinigeona
ratinamerikajuyi hagseubgwajeongeul anbaehayeo julgeosida. don Quijoteyi yuilhan mogpyoneun baro
pumjileul bojeunghaneunde issda. urideulro hayeogeum jarangseureobge saenggaghaneun geoseun uriyi saeroun
hagweonyi 50%ga gijonhagweondeuli cuceonhan geosiraneun geosida <<
>>Vr sa god<<