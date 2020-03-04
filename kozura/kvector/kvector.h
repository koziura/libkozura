#ifndef __KVECTOR_H__
#define __KVECTOR_H__
///
#include <memory.h>
#include <boost/container/vector.hpp>
#include <boost/move/move.hpp>
/*!
 * \brief kvector_t
 */
template<typename T>
class kvector_t {
	//BOOST_COPYABLE_AND_MOVABLE(kvector_t)
public:
	typedef typename boost::container::vector<T> VecType;
	typedef typename VecType::const_iterator const_iterator;
	typedef typename VecType::iterator iterator;
	typedef typename VecType::value_type value_type;
	/*!
	 * \brief kvector_t
	 */
	inline kvector_t() {

	}
	/*!
	 * \brief kvector_t
	 * \param size_
	 */
	inline kvector_t(uint32_t size_) {
		m_array.reserve(0);
		m_array.resize(size_);
	}
	inline ~kvector_t() {}
	/*!
	 * \brief kvector_t
	 * \param dt
	 * \param size
	 */
	inline kvector_t(const T dt[], uint32_t count) {
		m_array.resize(count);
		memcpy(&m_array[0], &dt[0], count * sizeof(T));
	}
	/*!
	 * \brief kvector_t
	 * \param other
	 */
	inline kvector_t(const kvector_t& other) {
		m_array = other.m_array;
	}
	/*!
	 * \brief kvector_t
	 * \param other
	 */
	inline kvector_t(const VecType& other) {
		m_array = other;
	}
#if __cplusplus > 199711L
	/*!
	 * \brief kvector_t
	 * \param other
	 */
	inline kvector_t(const kvector_t&& o) noexcept :
	m_array(std::move(o.m_array)) {

	}
	/*!
	 * \brief operator =
	 * \param o
	 * \return
	 */
	inline kvector_t& operator=(const kvector_t&& o) {
		m_array = std::move(o.m_array);
		return *this;
	}
#endif
	/*!
	 * \brief erase
	 * \param it
	 * \return
	 */
	inline const_iterator erase(const_iterator it) {
		return m_array.erase(it);
	}
	/*!
	 * \brief erase
	 * \param begin
	 * \param end
	 * \return
	 */
	inline const_iterator erase(const_iterator begin, const_iterator end) {
		return m_array.erase(begin, end);
	}
	/*!
	 * \brief operator =
	 * \param o
	 * \return
	 */
	inline kvector_t& operator=(const kvector_t& o) {
		m_array = o.m_array;
		return *this;
	}
	/*!
	 * \brief operator +=
	 * \param o
	 * \return
	 */
	inline kvector_t& operator+=(const kvector_t& o) {
		append( o );
		return *this;
	}
	/*!
	 * \brief operator +=
	 * \param e
	 * \return
	 */
	inline kvector_t& operator+=(const T& e) {
		const_iterator it = m_array.end();
		m_array.insert(it, e);
		return *this;
	}
	/*!
	 * \brief begin
	 * \return
	 */
	inline iterator begin() {
		return m_array.begin();
	}
	/*!
	 * \brief end
	 * \return
	 */
	inline iterator end() {
		return m_array.end();
	}
	/*!
	 * \brief begin
	 * \return
	 */
	inline const_iterator begin() const {
		return m_array.begin();
	}
	/*!
	 * \brief end
	 * \return
	 */
	inline const_iterator end() const {
		return m_array.end();
	}
	/*!
	 * \brief append
	 * \param dt
	 * \param size
	 */
	inline void append(const T dt[], uint32_t count) {
		size_t base_count = m_array.size();
		m_array.resize(base_count + count);
		memcpy(&m_array[0] + (base_count * sizeof(T)), dt, count * sizeof(T));
	}
	/*!
	 * \brief append
	 * \param other
	 */
	inline void append(const kvector_t& other) {
		m_array.insert(m_array.end(), other.begin(), other.end());
	}
	/*!
	 * \brief insert
	 * \param pos
	 * \param element
	 */
	inline void insert(const size_t& pos, const T& element) {
		const_iterator it = m_array.begin() + pos;
		m_array.insert(it, element);
	}
	/*!
	 * \brief erase
	 * \param it
	 * \return
	 */
	inline iterator erase(iterator it) {
		return m_array.erase(it);
	}
	/*!
	 * \brief setRawData
	 * \param dt
	 * \param size
	 */
	inline void setRawData(const T dt[], uint32_t count) {
		size_t base_count = count;
		m_array.resize(base_count);
		memcpy(&m_array[0], dt, count * sizeof(T));
	}
	/*!
	 * \brief constData
	 * \return
	 */
	inline const T* constData() const {
		return &m_array[0];
	}
	/*!
	 * \brief data
	 * \return
	 */
	inline T* data() {
		return &m_array[0];
	}
	/*!
	 * \brief length
	 * \return
	 */
	inline int length() const {
		return static_cast<int>(m_array.size());
	}
	/*!
	 * \brief push_back
	 * \param val
	 */
	inline void push_back(const T& val) {
		m_array.push_back(val);
	}
	/*!
	 * \brief append
	 * \param val
	 */
	inline void append(const T& val) {
		m_array.push_back(val);
	}
	/*!
	 * \brief size
	 * \return
	 */
	inline size_t size() const {
		return m_array.size();
	}
	/*!
	 * \brief bytes
	 * \return
	 */
	inline size_t bytes() const {
		return m_array.size() * sizeof(T);
	}
	/*!
	 * \brief operator []
	 * \param t
	 * \return
	 */
	inline T& operator[](const size_t& id) {
		return m_array[id];
	}
	/*!
	 * \brief operator []
	 * \param id
	 * \return
	 */
	inline const T& operator[](const size_t& id) const {
		return m_array[id];
	}
	/*!
	 * \brief clear
	 */
	inline void clear() {
		m_array.clear();
	}
	/*!
	 * \brief reserve
	 * \param id
	 */
	inline void reserve(size_t id) {
		m_array.reserve(id);
	}
	/*!
	 * \brief resize
	 * \param id
	 */
	inline void resize(size_t id) {
		m_array.resize(id);
	}
	/*!
	 * \brief at
	 * \param id
	 * \return
	 */
	inline const T& at(const size_t& id) {
		return m_array.at(id);
	}
	/*!
	 * \brief operator ==
	 * \param o
	 * \return
	 */
	inline bool operator ==(const kvector_t& o) const {
		return m_array == o.m_array;
	}
	/*!
	 * \brief operator !=
	 * \param o
	 * \return
	 */
	inline bool operator !=(const kvector_t& o) const {
		return !(*this == o);
	}
	/*!
	 * \brief tovector
	 * \return
	 */
	inline const VecType& toVectorType() const {
		return m_array;
	}
	/*!
	 * \brief tovector
	 * \return
	 */
	inline VecType& toVectorType() {
		return m_array;
	}
	//
protected:
	VecType m_array;
};
///
#endif // __KVECTOR_H__
///
