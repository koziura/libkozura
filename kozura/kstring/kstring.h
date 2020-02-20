///
#ifndef __KZR_STRING_H__
#define __KZR_STRING_H__
///
#include <stdlib.h>
#include <cstring>
/*!
 * Namespace by Kozura(c) Inc.
 */
namespace kozura {
typedef unsigned int uint_t;
/*!
 * \brief The knoinheritance_t class
 */
class knoinheritance_t {
	friend class kstring_t;
	inline knoinheritance_t(){}
	inline knoinheritance_t(const knoinheritance_t&){}
	virtual ~knoinheritance_t(){}
};
/*!
 * \brief The kstring_t class
 */
class kstring_t:
		virtual private knoinheritance_t
{
	char* m_cstr;
	uint_t m_len;
	uint_t m_reserve;
///
public:
	/*! */
	inline ~kstring_t() {
		clear();
	}
	/*!
	 * \brief kstring_t
	 */
	inline kstring_t():
		m_cstr(NULL), m_len(0), m_reserve(1) {
	}
	/*!
	 * \brief kstring_t
	 * \param str
	 */
	inline kstring_t(const char* str): m_reserve(1) {
		m_len = strlen(str);
		m_cstr = (char*)malloc(m_len+m_reserve);
		memcpy(m_cstr, str, m_len);
		m_cstr[m_len] = 0;
	}
	/*!
	 * \brief kstring_t
	 * \param str
	 */
	inline kstring_t(const kstring_t& str) {
		m_len = str.size();
		m_reserve = str.m_reserve;
		m_cstr = (char*)malloc(m_len+m_reserve);
		memcpy(m_cstr, str.m_cstr, m_len);
		if (m_len) {
			m_cstr[m_len] = '\0';
		}
	}
	/*!
	 * \brief operator =
	 * \param str
	 * \return
	 */
	inline kstring_t& operator =(const char* str) {
		uint_t len = strlen(str);

		if (len != m_len) {
			clear();
		}
		m_len = len;
		m_cstr = (char*)malloc(m_len+m_reserve);
		if (m_len) {
			memcpy(m_cstr, str, m_len);
		}
		m_cstr[m_len] = '\0';
		return *this;
	}
	/*!
	 * \brief operator =
	 * \param str
	 * \return
	 */
	inline kstring_t& operator =(const kstring_t& str) {
		uint_t len = str.size();

		if (len != m_len) {
			clear();
		}
		m_len = len;
		m_reserve = str.m_reserve;
		m_cstr = (char*)malloc(m_len+m_reserve);
		if (m_len) {
			memcpy(m_cstr, str.c_str(), m_len);
		}
		m_cstr[m_len] = '\0';
		return *this;
	}
	/*!
	 * \brief operator +=
	 * \param ch
	 * \return
	 */
	inline kstring_t& operator +=(const char ch) {
		uint_t len = 1;

		if (m_cstr) {
			m_cstr = (char*)realloc(m_cstr, m_len+len+m_reserve);
		} else {
			m_cstr = (char*)malloc(len+m_reserve);
		}
		memcpy(m_cstr + m_len, &ch, len);
		m_len += len;
		m_cstr[m_len] = '\0';
		return *this;
	}
	/*!
	 * \brief operator +=
	 * \param str
	 * \return
	 */
	inline kstring_t& operator +=(const char* str) {
		uint_t len = strlen(str);

		if (m_cstr) {
			m_cstr = (char*)realloc(m_cstr, m_len+len+m_reserve);
		} else {
			m_cstr = (char*)malloc(len+m_reserve);
		}
		memcpy(m_cstr + m_len, str, len);
		m_len += len;
		m_cstr[m_len] = '\0';
		return *this;
	}
	/*!
	 * \brief operator +=
	 * \param str
	 * \return
	 */
	inline kstring_t& operator +=(const kstring_t& str) {
		uint_t len = str.size();

		if (m_cstr) {
			m_cstr = (char*)realloc(m_cstr, m_len+len+m_reserve);
		} else {
			m_cstr = (char*)malloc(len+m_reserve);
		}
		memcpy(m_cstr + m_len, str.m_cstr, len);
		m_len += len;
		m_cstr[m_len] = '\0';
		return *this;
	}
	/*!
	 * \brief operator +
	 * \param str
	 * \return
	 */
	inline inline kstring_t operator +(const kstring_t& str) const {
		kstring_t local = *this;
		return local+=(str);
	}
	/*!
	 * \brief operator +
	 * \param str
	 * \return
	 */
	inline kstring_t operator +(const char* str) const {
		kstring_t local = *this;
		return local+=(str);
	}
	/*!
	 * \brief operator ==
	 * \param str
	 * \return
	 */
	inline bool operator ==(const kstring_t& str) {
		const char* pattern = m_cstr;
		const char* string = str.c_str();

		if (!pattern || !string) {
			return false;
		}

		int sz1 = strlen(pattern);
		int sz2 = strlen(string);

		if (string[sz2-1] == '\n') {
			--sz2;
		}

		if (sz1 != sz2) {
			return false;
		}

		const char* b = pattern;
		const char* s = string;

		while ( *s != '\0' && *s != '\n' ) {
			if (*b == *s) {
				++b;
				++s;
			} else {
				return false;
			}
		}
		return true;
	}
	/*!
	 * \brief operator !=
	 * \param str
	 * \return
	 */
	inline bool operator !=(const kstring_t& str) {
		return !(*this == str);
	}
	/*!
	 * \brief size
	 * \return
	 */
	inline uint_t size() const {
		return m_len;
	}
	/*!
	 * \brief at
	 * \param pos
	 * \return
	 */
	inline const char& at(const uint_t& pos) const {
		return m_cstr[pos];
	}
	/*!
	 * \brief operator []
	 * \param pos
	 * \return
	 */
	inline char& operator [](const uint_t& pos) {
		return m_cstr[pos];
	}	/*!
	 * \brief c_str
	 * \return
	 */
	inline const char* c_str() const {
		return m_cstr;
	}
	/*!
	 * \brief empty
	 * \return
	 */
	inline bool empty() const {
		return !m_len;
	}
	/*!
	 * \brief isNull
	 * \return
	 */
	inline bool isNull() const {
		return m_cstr == NULL;
	}
	/*!
	 * \brief clear
	 */
	inline void clear() {
		if (m_cstr) {
			free(m_cstr);
		}
		m_len = 0;
		m_cstr = NULL;
	}
	/*!
	 * \brief string_cast
	 * \param val
	 * \return
	 */
	static kstring_t string_cast(int val) {
		char lcbuf[255];
		sprintf(lcbuf, "%d", val);
		return kstring_t(lcbuf);
	}
	/*!
	 * \brief lstring_cast
	 * \param val
	 * \return
	 */
	static kstring_t string_cast(unsigned int val) {
		char lcbuf[255];
		sprintf(lcbuf, "%d", val);
		return kstring_t(lcbuf);
	}
	/*!
	 * \brief string_cast
	 * \param val
	 * \return
	 */
	static kstring_t string_cast(double val) {
		char lcbuf[255];
		sprintf(lcbuf, "%f", val);
		return kstring_t(lcbuf);
	}
};
/*!
 * \brief operator +
 * \param c_str
 * \param str
 * \return
 */
inline kstring_t operator +(const char* c_str, const kstring_t& str) {
	return kstring_t(c_str) + str;
}
/*!
 * \brief operator ==
 * \param c_str
 * \param str
 * \return
 */
inline bool operator ==(const char* c_str, const kstring_t& str) {
	return kstring_t(c_str) == str;
}
/*!
 * \brief operator !=
 * \param c_str
 * \param str
 * \return
 */
inline bool operator !=(const char* c_str, const kstring_t& str) {
	return kstring_t(c_str) != str;
}
///
} // Namespace by Kozura(c) Inc.
#endif //__KZR_STRING_H__
///
