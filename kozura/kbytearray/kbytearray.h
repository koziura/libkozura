#ifndef __KBYTEARRAY_H__
#define __KBYTEARRAY_H__
///
#include <boost/container/string.hpp>
#include <kozura/vector>
/*!
 * Namespace by Kozura(c) Inc.
 */
namespace kozura {
/*!
 * \brief kbytearray_t
 */
class kbytearray_t:
		public kvector_t<char> {
	//
public:
#if __cplusplus > 199711L
	using kvector_t<char>::kvector_t;
	inline kbytearray_t() = default;
#else
	/*!
	 * \brief kbytearray_t
	 */
	inline kbytearray_t() {}
	/*!
	 * \brief kbytearray_t
	 * \param size_
	 */
	inline kbytearray_t(uint32_t size_):
		kvector_t<char>(size_)
	{
	}
#endif
	/*!
	 * \brief kbytearray_t
	 * \param dt
	 * \param size
	 */
	inline kbytearray_t(const char dt[], uint32_t size=0) {
		if (!size) {
			size = static_cast<uint32_t>( strlen(dt) );
		}
		m_array.resize(size);
		memcpy(&m_array[0], &dt[0], size);
	}
	/*!
	 * \brief append
	 * \param dt
	 * \param size
	 */
	inline void append(const char dt[], uint32_t size=0) {
		if (!size) {
			size = static_cast<uint32_t>(strlen(dt));
		}
		size_t base_size = m_array.size();
		m_array.resize(base_size + size);
		memcpy(&m_array[0] + base_size, dt, size);
	}
	/*!
	 * \brief setRawData
	 * \param dt
	 * \param size
	 */
	inline void setRawData(const char dt[], uint32_t size=0) {
		if (!size) {
			size = static_cast<uint32_t>(strlen(dt));
		}
		size_t base_size = size;
		m_array.resize(base_size);
		memcpy(&m_array[0], dt, size);
	}
	/*!
	 * \brief operator <<
	 * \param cstr
	 * \return
	 */\
	inline kbytearray_t& operator <<(const boost::container::string& str) {
		append( str.c_str(), static_cast<uint32_t>(str.length()) );
		return *this;
	}
	/*!
	 * \brief str
	 * \return
	 */
	inline boost::container::string str() const {
		return boost::container::string(&m_array[0], m_array.size());
	}
};
} // Namespace by Kozura(c) Inc.
#endif // __KBYTEARRAY_H__
///
