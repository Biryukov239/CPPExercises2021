#pragma once

#include <opencv2/highgui.hpp>

#include <vector>

// Р—РґРµСЃСЊ РјС‹ Р±СѓРґРµРј С…СЂР°РЅРёС‚СЊ РїР°СЂР°РјРµС‚СЂС‹ РЅР°С€РµРіРѕ Р°Р»РіРѕСЂРёС‚РјР°:
#define NBINS 16 // С‡РёСЃР»Рѕ РєРѕСЂР·РёРЅ (С‚.Рµ. РєРѕР»РёС‡РµСЃС‚РІРѕ СЂР°Р·РЅС‹С… РЅР°РїСЂР°РІР»РµРЅРёР№ СѓРіР»Р° РєРѕС‚РѕСЂС‹Рµ РјС‹ СЂР°СЃСЃРјР°С‚СЂРёРІР°РµРј)


typedef std::vector<float> HoG;


HoG buildHoG(cv::Mat grad_x, cv::Mat grad_y); // РїСЂРёРЅРёРјР°РµС‚ РЅР° РІС…РѕРґ РіСЂР°РґРёРµРЅС‚С‹ РїРѕ РѕР±РµРёРј РѕСЃСЏРј

HoG buildHoG(const cv::Mat& originalImg); // РїСЂРёРЅРёРјР°РµС‚ РЅР° РІС…РѕРґ РѕСЂРёРіРёРЅР°Р»СЊРЅСѓСЋ РєР°СЂС‚РёРЅРєСѓ Рё РІС‹Р·С‹РІР°РµС‚ С„СѓРЅРєС†РёСЋ buildHoG РѕР±СЉСЏРІР»РµРЅРЅСѓСЋ РІС‹С€Рµ


std::ostream& operator << (std::ostream& os, const HoG& hog);


double distance(HoG a, HoG b);
