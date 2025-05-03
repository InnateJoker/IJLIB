#ifndef IJINT_HPP
#define IJINT_HPP

#include <stack>
#include <cstring>
#include <iostream>
#define _IJint(x) IJint::intTOIJint(x)
using namespace std;

namespace ij {
	class IJint {
	private:
		static const int BIT = 2045;
		short num[BIT + 1];
		inline void getsize() {
			int i = BIT;
			while(i >= 0 && num[i] == 0) {
				i -- ;
			}
			if(i == -1) {
				size = 1;
			}
			else {
				size = i + 1;
			}
		}
		short cmp[BIT + 1];
		bool PrintBool() {
			memset(cmp,0,sizeof(cmp));
			if(memcmp(num,cmp,sizeof(short) * BIT) == 0) {
				return true;
			}
			return false;
		}
	public:
		int size;
		bool porn;
		inline void init() {
			for(int i = 0; i <= BIT; i++) {
				num[i] = 0;
			}
		}
		static IJint intTOIJint(int n) {
			IJint ans;
			ans.init();
			if(n < 0) {
				ans.porn = false;
				n = -n;
			} else {
				ans.porn = true;
			}
			int p = 0;
			while(n != 0) {
				ans.num[p++]=n % 10;
				n /= 10;
			}
			ans.getsize();
			return ans;
		}
		void read() {
			init();
			stack <short> st;
			size = 0;
			memset(num,0,sizeof(num));
			char a;
			bool c = true;
			bool fr0 = true;
			a = getchar();
			while(1) {
				if(!((a >= '0' && a <= '9') || a == '-') || (c == false && a == '-')) {
					break;
				}
				if(a == '-') {
					size -- ;
					porn = false;
				} else if(fr0 == false) {
					st.push(a - '0');
				}
				else if(fr0 == true && a != '0') {
					st.push(a - '0');
					fr0 = false;
				} else {
					size -- ;
				}
				if(c == true) {
					c = false;
				}
				size++;
				a = getchar();
			}
			for(int i = 0; i < size; i++) {
				num[i] = st.top();
				st.pop();
			}
			if(size == 0) {
				size = 1;
				num[0] = 0;
			}
		}
		void print() {
			if(num[0] == -8) {
				printf("Runtime Error! Zero(0) cannot be a divisor!");
				return;
			}
			if(num[0] == -9) {
				printf("Runtime Error! Zero(0) to the power of zero(0) is undefined!");
				return;
			}
			if(PrintBool() == true) {
				printf("0");
				return;
			}
			if(porn == false) printf("-");
			int p=size - 1;
			while(p != -1) {
				printf("%d",num[p]);
				p -- ;
			}
		}
		void operator ^ (IJint &a) {
			IJint t;
			t = *this;
			*this = a;
			a = t;
		}
		void operator = (const IJint a) {
			memcpy(num,a.num,sizeof(short) * BIT);
			porn = a.porn;
			size = a.size;
		}
		bool operator ! () {
			return *this == 0;
		}
		IJint abs() {
			IJint ret;
			ret = *this;
			ret.porn = true;
			return ret;
		}
		IJint opp() {
			IJint ret;
			ret = *this;
			ret.porn = !ret.porn;
			return ret;
		}
		bool operator > (const IJint a) const {
			if(porn == true && a.porn == false) {
				return true;
			}
			if(porn == false && a.porn == true) {
				return false;
			}
			bool ret = false;
			int bit = max(size,a.size);
			for(int i = bit - 1; i >= 0; i -- ) {
				if(num[i] > a.num[i]) {
					ret = true;
					break;
				} else if(num[i] < a.num[i]) {
					ret = false;
					break;
				}
			}
			if(porn == false) {
				return !ret;
			}
			return ret;
		}
		bool operator < (const IJint a) const {
			if(porn == true && a.porn == false) {
				return false;
			}
			if(porn == false && a.porn == true) {
				return true;
			}
			bool ret = false;
			int bit = max(size,a.size);
			for(int i = bit - 1; i >= 0; i -- ) {
				if(num[i] < a.num[i]) {
					ret = true;
					break;
				} else if(num[i] > a.num[i]) {
					ret = false;
					break;
				}
			}
			if(porn == false) {
				return !ret;
			}
			return ret;
		}
		bool operator == (const IJint a) const {
			if(porn != a.porn) {
				return false;
			}
			int bit = max(size,a.size);
			for(int i = bit - 1; i >= 0; i -- ) {
				if(num[i] != a.num[i]) {
					return false;
				}
			}
			return true;
		}
		bool operator != (const IJint a) const {
			return ! (*this == a);
		}
		bool operator >= (const IJint a) const {
			return *this>a || *this==a;
		}
		bool operator <= (const IJint a) const {
			return *this<a || *this==a;
		}
		IJint operator + (const IJint a) const {
			IJint ans;
			ans.init();
			if(porn == a.porn) {
				ans.porn = porn;
				int bit = max(size,a.size);
				for(int i = 0; i < bit; i++) {
					ans.num[i] += num[i] + a.num[i];
					ans.num[i+1] = ans.num[i] / 10;
					ans.num[i] %= 10;
				}
			} else {
				IJint b = a;
				IJint _this = *this;
				ans.porn = (b.abs() > _this.abs()) ? a.porn : porn;
				int bit = max(size,a.size);
			label:
				for(int i = 0; i < bit; i++) {
					ans.num[i] += b.num[i] - _this.num[i];
					if(ans.num[i] < 0) {
						ans.num[i] += 10;
						ans.num[i + 1] -- ;
					}
				}
				if(ans.num[bit] < 0) {
					memset(ans.num,0,sizeof(short) * BIT);
					b ^ _this;
					goto label;
				}
			}
			ans.getsize();
			return ans;
		}
		IJint operator - (const IJint a) const {
			IJint ans;
			ans.init();
			if(porn == a.porn) {
				IJint b = a;
				IJint _this = *this;
				ans.porn = (b.abs() < _this.abs()) ? porn : !porn;

				int bit = max(size,a.size);
				if(ans.porn != porn) b ^ _this;
				for(int i = 0; i < bit; i++) {
					ans.num[i] += _this.num[i] - b.num[i];
					if(ans.num[i] < 0) {
						ans.num[i] += 10;
						ans.num[i + 1] -- ;
					}
				}
			} else {
				ans.porn = porn;
				IJint b = a;
				b = b.opp();
				int bit = max(size,b.size);
				for(int i = 0; i < bit; i++) {
					ans.num[i] += num[i] + b.num[i];
					ans.num[i+1] = ans.num[i] / 10;
					ans.num[i] %= 10;
				}
			}
			ans.getsize();
			return ans;
		}
		void operator += (const IJint a) {
			*this = *this + a;
		}
		void operator -= (const IJint a) {
			*this = *this - a;
		}
		void operator++() {
			*this = *this + _IJint(1);
		}
		IJint operator++(int) {
			IJint *ret = this;
			++ *this;
			return *ret;
		}
		void operator -- () {
			*this = *this - _IJint(1);
		}
		IJint operator -- (int) {
			IJint *ret = this;
			-- *this;
			return *ret;
		}
		IJint operator * (const IJint a) const {
			IJint ans;
			ans.init();
			ans.porn = (porn == a.porn) ? true : false;

			for(int i = 0; i < size; i++) {
				for(int j = 0; j < a.size; j++) {
					ans.num[i + j] += num[i] * a.num[j];
				}
			}
			for(int i = 0; i < BIT; i++) {
				ans.num[i+1] += ans.num[i] / 10;
				ans.num[i] %= 10;
			}
			ans.getsize();
			return ans;
		}
		IJint operator / (const IJint a) const {
			if(a == _IJint(0)) {
				IJint re;
				re.init();
				re.num[0] = -8;
				return re;
			}
			IJint ans;
			ans.init();
			IJint _this = *this;
			IJint b = a;
			_this = _this.abs();
			b = b.abs();
			ans = _IJint(0);
			while(_this >= b) {
				_this -= b;
				ans++;
			}
			ans.porn = (porn == a.porn) ? true : false;
			ans.getsize();
			return ans;
		}
		IJint operator%(const IJint a) const {
			if(a == 0) {
				IJint re;
				re.init();
				re.num[0] = -8;
				return re;
			}
			IJint ans;
			ans.init();
			IJint _this = *this;
			IJint b = a;
			_this = _this.abs();
			b = b.abs();
			while(_this >= b)  {
				_this -= b;
			}
			if(porn == a.porn) ans = _this;
			else ans = b - _this;
			ans.porn = a.porn;
			ans.getsize();
			return ans;
		}
		void operator *= (const IJint a) {
			*this = *this*a;
		}
		void operator /= (const IJint a) {
			*this = *this / a;
		}
		void operator %= (const IJint a) {
			*this =* this % a;
		}
		IJint operator + (const int a) const {
			return *this + _IJint(a);
		}
		IJint operator - (const int a) const {
			return *this - _IJint(a);
		}
		IJint operator * (const int a) const {
			return *this * _IJint(a);
		}
		IJint operator / (const int a) const {
			return *this / _IJint(a);
		}
		IJint operator % (const int a) const {
			return *this % _IJint(a);
		}
		bool operator < (const int a) const {
			return *this < _IJint(a);
		}
		bool operator > (const int a) const {
			return *this > _IJint(a);
		}
		bool operator == (const int a) const {
			return *this == _IJint(a);
		}
		bool operator != (const int a) const {
			return *this != _IJint(a);
		}
		bool operator >= (const int a) const {
			return *this >= _IJint(a);
		}
		bool operator <= (const int a) const {
			return *this <= _IJint(a);
		}
		void operator += (const int a) {
			*this += _IJint(a);
		}
		void operator -= (const int a) {
			*this -= _IJint(a);
		}
		void operator *= (const int a) {
			*this *= _IJint(a);
		}
		void operator /= (const int a) {
			*this /= _IJint(a);
		}
		void operator %= (const int a) {
			*this %= _IJint(a);
		}
		void operator = (int a) {
			*this = _IJint(a);
		}
		friend IJint operator + (int a,IJint b) {
			return _IJint(a) + b;
		}
		friend IJint operator - (int a,IJint b) {
			return _IJint(a) - b;
		}
		friend IJint operator * (int a,IJint b) {
			return _IJint(a) * b;
		}
		friend IJint operator / (int a,IJint b) {
			return _IJint(a) / b;
		}
		friend IJint operator % (int a,IJint b) {
			return _IJint(a) % b;
		}
		IJint pow(IJint b) {
			if(b == 0 && *this != 0) {
				return _IJint(1);
			} else if(b == 0 && *this == 0) {
				IJint re;
				re.init();
				re.num[0] = -9;
				return re;
			}
			bool mui = true;
		label:
			IJint ret = *this;
			if(b.porn == true) {
				for(IJint i = 2; i <= b; i++) {
					ret *= *this;
				}
			} else {
				b = b.opp();
				mui = false;
				goto label;
			}
			if(mui == false)  {
				ret = 1 / ret;
			}
			ret.getsize();
			return ret;
		}
		IJint pow(int b) {
			return pow(_IJint(b));
		}
		IJint() {
			init();
			porn = true;
		}
		IJint(int n) {
			*this = _IJint(n);
			porn = true;
		}
		friend ostream& operator << (ostream &os,const IJint &n) {
			ios::sync_with_stdio(false);
			if(n.num[0] == -8) {
				os << "Runtime Error! Zero(0) cannot be a divisor!";
				return os;
			}
			if(n.num[0] == -9) {
				os << "Runtime Error! Zero(0) to the power of zero(0) is undefined!";
				return os;
			}
			IJint b = n;
			if(b.PrintBool() == true) {
				os << "0";
				return os;
			}
			if(n.porn == false) os << "-";
			int p = n.size - 1;
			while(p != -1) {
				os << n.num[p];
				p -- ;
			}
			return os;
		}
		friend istream& operator >> (istream &is,IJint &n) {
			ios::sync_with_stdio(false);
			n.init();
			stack <short> st;
			n.size = 0;
			memset(n.num,0,sizeof(num));
			char a;
			bool c = true;
			bool fr0 = true;
			a = getchar();
			while(1) {
				if(!((a >= '0' && a <= '9') || a=='-') || (c == false && a == '-'))  {
					break;
				}
				if(a == '-') {
					n.size -- ;
					n.porn = false;
				} else if(fr0 == false) {
					st.push(a - '0');
				}
				else if(fr0 == true && a != '0') {
					st.push(a - '0');
					fr0 = false;
				} else  {
					n.size -- ;
				}
				if(c == true) {
					c = false;
				}
				n.size++;
				a=getchar();
			}
			for(int i = 0; i < n.size; i++) {
				n.num[i] = st.top();
				st.pop();
			}
			if(n.size == 0) {
				n.size = 1;
				n.num[0] = 0;
			}
			return is;
		}
		operator bool() {
			return *this != 0;
		}
		operator short() {
			if (*this > 32767) {
				return 32767;
			} else if (*this < -32768) {
				return -32768;
			} else {
				short ret = 0;
				for (int k = 4; k >= 0; k--) {
					ret = ret * 10 + short(num[k]);
				}
				if (*this < 0) {
					ret = -ret;
				}
				return ret;
			}
		}
		operator int() {
			if (*this > 2147483647) {
				return 2147483647;
			} else if (*this < -2147483648) {
				return -2147483648;
			} else {
				int ret = 0;
				for (int k = 9; k >= 0; k--) {
					ret = ret * 10 + short(num[k]);
				}
				if (*this < 0) {
					ret = -ret;
				}
				return ret;
			}
		}
		operator unsigned int() {
			if (*this > 4294967295) {
				return 4294967295;
			} else if (*this < 0) {
				return 0;
			} else {
				unsigned int ret = 0;
				for (int k = 9; k >= 0; k--) {
					ret = ret * 10 + short(num[k]);
				}
				if (*this < 0) {
					ret = -ret;
				}
				return ret;
			}
		}
		operator long long() {
			if (*this > 9223372036854775807) {
				return 9223372036854775807;
			} else if (*this < -9223372036854775808) {
				return -9223372036854775808;
			} else {
				long long ret = 0;
				for (int k = 18; k >= 0; k--) {
					ret = ret * 10 + short(num[k]);
				}
				if (*this < 0) {
					ret = -ret;
				}
				return ret;
			}
		}
		operator unsigned long long() {
			if (*this > 18446744073709551615) {
				return 18446744073709551615;
			} else if (*this < 0) {
				return 0;
			} else {
				unsigned long long ret = 0;
				for (int k = 18; k >= 0; k--) {
					ret = ret * 10 + short(num[k]);
				}
				if (*this < 0) {
					ret = -ret;
				}
				return ret;
			}
		}
	};
} // namespace IJ

#endif // IJINT_HPP