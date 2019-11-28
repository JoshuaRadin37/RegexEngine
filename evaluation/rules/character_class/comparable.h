//
// Created by jradi on 11/6/2019.
//

#ifndef REGEXENGINE_COMPARABLE_H
#define REGEXENGINE_COMPARABLE_H




template <typename T, typename R>
class comparator;
template <typename T>
class simple_comparator;

template <typename T>
class natural_comparator;

template <typename T>
class comparable {
public:
	//typedef  comparator;
	typedef natural_comparator<T> comparator;
	
	virtual int compare_to(const T& other) const = 0;
	
	bool operator<(const T& other) const {
		return compare_to(other) < 0;
	}
	
	bool operator>(const T& other) const {
		return other < this;
	}
	
	bool operator>=(const T& other) const {
		return !(this < other);
	}
	
	bool operator<=(const T& other) const {
		return !(this > other);
	}
	
	bool operator==(const T& other) const {
		return compare_to(other) == 0;
	}
	
	bool operator!=(const T& other) const {
		return compare_to(other) != 0;
	}
	
	
};


template <typename T>
int compare(comparable<T>* o1, T o2) {
	return o1->compare_to(o2);
}


template <typename T>
int compare(const comparable<T>& o1, T o2) {
	return o1.compare_to(o2);
}



template <typename T, typename R>
class comparator {
public:
	virtual int compare(const T& o1, const R& o2) const = 0;
	int operator()(const T& o1, const R& o2) const {
		return compare(o1, o2);
	}
};

template <typename T, typename R>
int compare(const T& o1, const R& o2, comparator<T, R> *comp) {
	return (*comp)(o1, o2);
}

template <typename T, typename R>
int compare(const T& o1, const R& o2, comparator<comparable<R>, R> *comp) {
	return (*comp)(o1, o2);
}

template <typename T>
class simple_comparator : public comparator<T, T>{
public:
	virtual int compare(const T &o1, const T &o2) const = 0;
};

template <typename T>
class natural_comparator : public comparator<comparable<T>, T> {
public:
	int compare(const comparable<T> &o1, const T &o2) const override {
		return o1.compare_to(o2);
	}
	
};








#endif //REGEXENGINE_COMPARABLE_H
