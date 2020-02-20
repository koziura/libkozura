#ifndef __KZR_ARRAY_H__
#define __KZR_ARRAY_H__
/*!
 * Namespace by Kozura(c) Inc.
 */
namespace kozura {
typedef unsigned int uint_t;
typedef unsigned char uchar_t;
/*!
 * \brief The karray_t class
 */
template<typename T>
class karray_t {
	T* m_data;
	uint_t m_size;
	uint_t m_count;
	uint_t m_reserve;

public:
	/*!*/
	~karray_t() {
		clear();
	}
	/*!
	 * \brief kstring_t
	 */
	karray_t():
		m_data(NULL), m_size(0), m_count(0), m_reserve(0) {
	}
	/*!
	 * \brief kstring_t
	 * \param size
	 */
	karray_t(const uint_t& size):
		m_data(NULL), m_size(size), m_count(0), m_reserve(10)
	{
		m_data = (T*)malloc((m_size+m_reserve) * sizeof(T));
		for (uint_t i(0); i < m_size; ++i) {
			new(&m_data[i])T;
		}
		m_size += m_reserve;
	}
	/*!
	 * \brief kstring_t
	 * \param arr
	 */
	karray_t(const karray_t& arr):
		m_size(arr.m_size), m_count(arr.m_count), m_reserve(arr.m_reserve)
	{
		m_data = (T*)malloc(m_size * sizeof(T));
		for (uint_t i(0); i < m_size; ++i) {
			new(&m_data[i])T(arr.m_data[i]);
		}
	}
	/*!
	 * \brief size
	 * \return
	 */
	uint_t size() const {
		return m_count;
	}
	/*!
	 * \brief capacity
	 * \return
	 */
	uint_t capacity() const {
		return m_count + m_reserve;
	}
	/*!
	 * \brief at
	 * \param pos
	 * \return
	 */
	const T& at(const uint_t& pos) const {
		const T* elem = &m_data[pos];
		return *elem;
	}
	/*!
	 * \brief operator []
	 * \param pos
	 * \return
	 */
	T& operator [](const uint_t& pos) {
		T* elem = &m_data[pos];
		return *elem;
	}
	/*!
	 * \brief operator =
	 * \param arr
	 * \return
	 */
	karray_t& operator =(const karray_t& arr) {
		clear();
		m_size = arr.m_size;
		m_count = arr.m_count;
		m_reserve = arr.m_reserve;
		m_data = (T*)malloc(m_size * sizeof(T));
		for (uint_t i(0); i < m_size; ++i) {
			new(&m_data[i])T(arr.m_data[i]);
		}
		return *this;
	}
	/*!
	 * \brief addItem
	 * \param item
	 */
	void addItem(const T& item) {
		reserve();

		T* elem = &m_data[m_count];
		*elem = item;
		++m_count;

		if (m_reserve) {
			--m_reserve;
		}
	}
	/*!
	 * \brief data
	 * \return
	 */
	T* data() {
		return &m_data[0];
	}
	/*!
	 * \brief data
	 * \return
	 */
	const T* data() const {
		return &m_data[0];
	}
	/*!
	 * \brief clear
	 */
	void clear() {
		if (m_data) {
			for (uint_t i(0); i < m_size; ++i) {
				T* elem = &m_data[i];
				T& item = *elem;
				item.~T();
			}
			free(m_data);
		}
		m_size = m_count = m_reserve = 0;
		m_data = NULL;
	}

private:
	/*!
	 * \brief reserve
	 */
	void reserve() {
		if (m_reserve) {
			return;
		} else {
			m_reserve = 10;
		}

		if (!m_data) {
			m_data = (T*)malloc((m_size+m_reserve) * sizeof(T));
			m_size += m_reserve;
			for (uint_t i(0); i < m_size; ++i) {
				new(&m_data[i])T;
			}
		} else {
			T* array_ = (T*)malloc((m_size+m_reserve) * sizeof(T));
			memcpy((void*)array_, (void*)m_data, m_size * sizeof(T));
			free(m_data);
			for (unsigned i(0); i < m_reserve; ++i) {
				new(&array_[m_size + i])T;
			}
			m_data = array_;
			m_size += m_reserve;
		}
	}
};
} // Namespace by Kozura(c) Inc.
#endif // __KZR_ARRAY_H__
