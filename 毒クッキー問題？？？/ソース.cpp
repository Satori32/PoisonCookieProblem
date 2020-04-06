#include <iostream>
#include <cstdint>
#include <vector>
#include <tuple>

//Poison Cookie Problem.

typedef std::tuple<std::uintmax_t, std::uintmax_t, std::uintmax_t> Data;
typedef std::vector<std::uint8_t> DType;

namespace Cookie {
	enum {
		Normal=1,
		Medic,
		Poison
	};
}

std::tuple<DType,std::uintmax_t> PoisonCookieII(std::intmax_t NC, std::intmax_t CC, std::uintmax_t PC) {

	bool IsPoison = false;
	std::uintmax_t L = NC + CC + PC;
	DType R;
	std::uintmax_t C = 0;


	for (std::uintmax_t i = 0; i < L; i++) {
		if (!IsPoison) {
			if (PC) {
				PC--;
				IsPoison = true;
				R.push_back(Cookie::Poison);
				C++;
			}
		}
		if (NC) {
			if (NC) {
				NC--;
				IsPoison = false;
				R.push_back(Cookie::Normal);
			}
		}
		else {
			if (CC) {
				CC--;
				IsPoison = false;
				R.push_back(Cookie::Medic);
				C++;
			}
		}
		if (IsPoison) {
			if (PC) {
				R.push_back(Cookie::Poison);
				break;
			}
		}

	}

	return { R,C };
}

bool PoisonCookie(std::intmax_t NC, std::intmax_t CC, std::uintmax_t PC, bool IsP, std::uintmax_t GC, std::uintmax_t& MC, DType Score, DType& Max) {
	if (NC) {
		Score.push_back(Cookie::Normal);
		PoisonCookie(NC - 1, CC, PC, false, GC, MC, Score, Max);
		Score.pop_back();
	}

	if (CC) {
		Score.push_back(Cookie::Medic);
		PoisonCookie(NC, CC - 1, PC, false, GC + 1, MC, Score, Max);
		Score.pop_back();
	}

	if (PC) {
		Score.push_back(Cookie::Poison);
		if (IsP == true) {
			Score.pop_back();
			if (GC > MC) {
				MC = GC;
				Max = Score;
			}
			return false;
		}

		PoisonCookie(NC, CC, PC - 1, true, GC + 1, MC, Score, Max);
		Score.pop_back();
	}

	if (GC > MC) {
		MC = GC;
		Max = Score;
	}

	return true;
}

bool Show(DType D, std::uintmax_t CC,Data Cookie) {

	std::cout << "NGCure:" << std::get<0>(Cookie) << std::endl;
	std::cout << "GGCure:" << std::get<1>(Cookie) << std::endl;
	std::cout << "Poison:" << std::get<2>(Cookie) << std::endl;
	std::cout << "-------" << std::endl;

	std::uintmax_t C = 0;
	const char *Ch[] = { "Null", "NGCure","GGCure","Poison","Out..."};
	std::cout << "Count:" << CC << std::endl;
	for (auto& o : D) {
		std::cout << C++<<":" << Ch[o] << std::endl;
	}
	return true;
}

int main() {
	//Data Cookie{3,1,4};	
	Data Cookie{5,2,9};
	//Data Cookie{8,8,1};
	DType R;
	std::uintmax_t C = 0;

	//PoisonCookie(std::get<0>(Cookie),std::get<1>(Cookie),std::get<2>(Cookie), false,0,C, {}, R);
	//Show(R, C, Cookie);

	auto Tu = PoisonCookieII(std::get<0>(Cookie), std::get<1>(Cookie), std::get<2>(Cookie));
	Show(std::get<0>(Tu), std::get<1>(Tu), Cookie);

	return 0;


}