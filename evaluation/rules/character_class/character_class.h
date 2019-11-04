//
// Created by jradi on 11/4/2019.
//

#ifndef REGEXENGINE_CHARACTER_CLASS_H
#define REGEXENGINE_CHARACTER_CLASS_H

#include <iterator>
#include <vector>

class character_class{
private:
	template <typename T>
	class range {
	public:
		const T min;
		const T max;
		
		range(const T min, const T max) : min(min), max(max) {}
		class iterator{
		private:
			
			T current;
			
			explicit iterator(T val) {
				current = val;
			}
			friend class range<T>;
		public:
			const T& operator*() {
				return current;
			}
			
			iterator& operator++() {
				++current;
				return *this;
			}
			
			const iterator operator++(int) {
				auto clone = iterator(current);
				++(*this);
				return clone;
			}
			
			bool operator!=(iterator other) {
				return current != other.current;
			}
			
		};
		
		iterator begin() const {
			return iterator(min);
		}
		
		iterator end() const {
			return iterator(max + 1);
		}
	};
	
	template <typename T> class singleton : public range<T> {
	public:
		explicit singleton(const T o) : range<T>(o, o) {
		
		}
	};

	std::vector<range<char> *> ranges;
	void add_range(range<char> *r);
public:
	character_class();
	
	
	void add_range(char min, char max);
	void add_char(char c);
	
	class iterator {
	private:
		friend class character_class;
		std::vector<char> all_chars;
		int index = 0;
		explicit iterator(const std::vector<range<char> *>& ranges);
	
	public:
		const char& operator*();
		iterator& operator++();
		const iterator operator++(int);
		bool operator!=(iterator other);
	};
	
	iterator begin() const;
	const iterator end() const;
};


#endif //REGEXENGINE_CHARACTER_CLASS_H
