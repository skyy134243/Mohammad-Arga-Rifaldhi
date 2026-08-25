/**
 * LAPORKITA - Pure Vanilla JavaScript System Architecture
 * Civic-Tech Platform Prototype
 * 
 * PROTOTYPE ONLY — not production authentication
 */

(() => {
    'use strict';

    // =========================================================
    // 01. CONSTANTS & CONFIGURATION
    // =========================================================
    const STORAGE_KEYS = {
        USERS: 'laporkita_users',
        REPORTS: 'laporkita_reports',
        NOTIFICATIONS: 'laporkita_notifications',
        SESSION: 'laporkita_session',
        SETTINGS: 'laporkita_settings'
    };

    const MOCK_USERS = {
        CITIZEN: {
            id: 'USR-CITIZEN-001',
            name: 'Mohammad Arga',
            role: 'citizen',
            email: 'arga@example.com'
        },
        OFFICER: {
            id: 'USR-OFFICER-001',
            name: 'Petugas Wilayah',
            role: 'officer',
            region: 'Kecamatan Coblong',
            latitude: -6.8897,
            longitude: 107.6101
        }
    };

    const REPORT_CATEGORIES = {
        fasilitas: {
            label: 'Fasilitas',
            subcategories: ['Jalan rusak', 'Lampu jalan', 'Drainase', 'Trotoar', 'Fasilitas umum', 'Fasilitas sekolah']
        },
        pungli: {
            label: 'Dugaan Pungli',
            subcategories: ['Pungutan tidak jelas', 'Biaya di luar ketentuan', 'Tarif tidak sesuai informasi', 'Dugaan pungutan liar']
        },
        sosial: {
            label: 'Masalah Sosial',
            subcategories: ['Gangguan ketertiban', 'Konflik lingkungan', 'Gangguan fasilitas bersama', 'Permasalahan lingkungan permukiman']
        },
        lingkungan: {
            label: 'Lingkungan',
            subcategories: ['Sampah', 'Pencemaran', 'Limbah', 'Pembakaran sampah', 'Banjir', 'Polusi', 'Kerusakan ruang hijau', 'Drainase tersumbat']
        }
    };

    // Global App State
    const state = {
        currentUser: null,
        reports: [],
        notifications: [],
        mapInstance: null,
        markers: []
    };

    // =========================================================
    // 02. LOCAL STORAGE HELPERS & ERROR HANDLING
    // =========================================================
    function getStorage(key, defaultValue = null) {
        try {
            const item = localStorage.getItem(key);
            return item ? JSON.parse(item) : defaultValue;
        } catch (error) {
            console.error(`Error reading key "${key}" from localStorage:`, error);
            return defaultValue;
        }
    }

    function setStorage(key, value) {
        try {
            localStorage.setItem(key, JSON.stringify(value));
            return true;
        } catch (error) {
            console.error(`Error saving key "${key}" to localStorage:`, error);
            showUIError('Gagal menyimpan data ke penyimpanan lokal browser.');
            return false;
        }
    }

    function removeStorage(key) {
        try {
            localStorage.removeItem(key);
        } catch (error) {
            console.error(`Error removing key "${key}" from localStorage:`, error);
        }
    }

    // =========================================================
    // 03. UTILITIES & MATH (HAVERSINE FORMULA)
    // =========================================================
    function calculateDistance(lat1, lon1, lat2, lon2) {
        if (!lat1 || !lon1 || !lat2 || !lon2) return Infinity;
        const R = 6371; // Radius bumi dalam KM
        const dLat = (lat2 - lat1) * (Math.PI / 180);
        const dLon = (lon2 - lon1) * (Math.PI / 180);
        const a = 
            Math.sin(dLat / 2) * Math.sin(dLat / 2) +
            Math.cos(lat1 * (Math.PI / 180)) * Math.cos(lat2 * (Math.PI / 180)) * 
            Math.sin(dLon / 2) * Math.sin(dLon / 2);
        const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
        return R * c; // Jarak dalam KM
    }

    function formatDate(dateString) {
        if (!dateString) return '-';
        const date = new Date(dateString);
        return date.toLocaleDateString('id-ID', {
            day: 'numeric',
            month: 'Long',
            year: 'numeric'
        });
    }

    function generateReportId() {
        const reports = getStorage(STORAGE_KEYS.REPORTS, []);
        const year = new Date().getFullYear();
        let maxSeq = 0;
        
        reports.forEach(r => {
            if (r.id && r.id.startsWith(`LP-${year}-`)) {
                const seqStr = r.id.split('-')[2];
                const seq = parseInt(seqStr, 10);
                if (!isNaN(seq) && seq > maxSeq) {
                    maxSeq = seq;
                }
            }
        });

        const nextSeq = String(maxSeq + 1).padStart(6, '0');
        return `LP-${year}-${nextSeq}`;
    }

    function showUIError(message) {
        const errorContainer = document.querySelector('.error-placeholder') || document.createElement('div');
        errorContainer.textContent = message;
        errorContainer.style.display = 'block';
    }

    // =========================================================
    // 04. MOCK DATABASE SEEDING (20 REPORTS)
    // =========================================================
    function seedMockDatabase() {
        const existingReports = getStorage(STORAGE_KEYS.REPORTS);
        if (existingReports && Array.isArray(existingReports) && existingReports.length > 0) {
            return;
        }

        const dummyReports = [
            {
                id: 'LP-2026-000001',
                title: 'Jalan Berlubang Parah di Depan Pasar',
                category: 'fasilitas',
                subcategory: 'Jalan rusak',
                description: 'Jalan berlubang cukup dalam dan membahayakan pengendara motor terutama saat hujan tergenang air.',
                location: 'Jl. Dago No. 12',
                coordinates: { latitude: -6.8850, longitude: 107.6135 },
                date: '2026-08-01',
                time: '08:30',
                urgency: 'tinggi',
                status: 'completed',
                reporter: MOCK_USERS.CITIZEN,
                anonymous: false,
                images: [],
                updates: [
                    { status: 'reported', date: '2026-08-01 08:30', note: 'Laporan dibuat oleh masyarakat.', officer: null },
                    { status: 'verified', date: '2026-08-01 10:00', note: 'Laporan diverifikasi oleh petugas.', officer: 'Petugas Wilayah' },
                    { status: 'forwarded', date: '2026-08-01 11:30', note: 'Diteruskan ke Dinas PU.', officer: 'Petugas Wilayah' },
                    { status: 'processing', date: '2026-08-02 09:00', note: 'Penambalan jalan sedang dilakukan.', officer: 'Dinas PU' },
                    { status: 'completed', date: '2026-08-03 15:00', note: 'Penambalan jalan selesai.', officer: 'Dinas PU' }
                ],
                assignedOfficer: 'Petugas Wilayah',
                createdAt: '2026-08-01T08:30:00.000Z',
                updatedAt: '2026-08-03T15:00:00.000Z'
            },
            {
                id: 'LP-2026-000002',
                title: 'Lampu Jalan Mati Sepanjang Gang',
                category: 'fasilitas',
                subcategory: 'Lampu jalan',
                description: 'Sudah 3 hari lampu penerangan jalan umum mati total, kondisi gang sangat gelap.',
                location: 'Jl. Dipatiukur Gang 4',
                coordinates: { latitude: -6.8910, longitude: 107.6160 },
                date: '2026-08-10',
                time: '19:15',
                urgency: 'sedang',
                status: 'processing',
                reporter: MOCK_USERS.CITIZEN,
                anonymous: false,
                images: [],
                updates: [
                    { status: 'reported', date: '2026-08-10 19:15', note: 'Laporan masuk.', officer: null },
                    { status: 'verified', date: '2026-08-11 08:00', note: 'Data terverifikasi.', officer: 'Petugas Wilayah' },
                    { status: 'processing', date: '2026-08-11 13:00', note: 'Teknisi sedang melakukan perbaikan bola lampu.', officer: 'Petugas Wilayah' }
                ],
                assignedOfficer: 'Petugas Wilayah',
                createdAt: '2026-08-10T19:15:00.000Z',
                updatedAt: '2026-08-11T13:00:00.000Z'
            },
            {
                id: 'LP-2026-000003',
                title: 'Dugaan Pungli Parkir Liar Tanpa Tiket',
                category: 'pungli',
                subcategory: 'Pungutan tidak jelas',
                description: 'Ada oknum yang menarik tarif parkir 10rb tanpa karcis resmi di area taman publik.',
                location: 'Taman Ganesha',
                coordinates: { latitude: -6.8930, longitude: 107.6100 },
                date: '2026-08-12',
                time: '14:00',
                urgency: 'tinggi',
                status: 'forwarded',
                reporter: { id: 'USR-CITIZEN-002', name: 'Budi Santoso' },
                anonymous: true,
                images: [],
                updates: [
                    { status: 'reported', date: '2026-08-12 14:00', note: 'Laporan diterima anonim.', officer: null },
                    { status: 'verified', date: '2026-08-12 15:00', note: 'Laporan valid.', officer: 'Petugas Wilayah' },
                    { status: 'forwarded', date: '2026-08-12 16:00', note: 'Diteruskan ke Satpol PP.', officer: 'Petugas Wilayah' }
                ],
                assignedOfficer: 'Petugas Wilayah',
                createdAt: '2026-08-12T14:00:00.000Z',
                updatedAt: '2026-08-12T16:00:00.000Z'
            },
            {
                id: 'LP-2026-000004',
                title: 'Penumpukan Sampah Liar di Pinggir Sungai',
                category: 'lingkungan',
                subcategory: 'Sampah',
                description: 'Warga mencium bau menyengat akibat sampah menumpuk dan meluap ke badan jalan.',
                location: 'Jl. Cihampelas',
                coordinates: { latitude: -6.8950, longitude: 107.6040 },
                date: '2026-08-15',
                time: '07:00',
                urgency: 'darurat',
                status: 'verified',
                reporter: MOCK_USERS.CITIZEN,
                anonymous: false,
                images: [],
                updates: [
                    { status: 'reported', date: '2026-08-15 07:00', note: 'Laporan diterima.', officer: null },
                    { status: 'verified', date: '2026-08-15 08:30', note: 'Diverifikasi oleh petugas.', officer: 'Petugas Wilayah' }
                ],
                assignedOfficer: 'Petugas Wilayah',
                createdAt: '2026-08-15T07:00:00.000Z',
                updatedAt: '2026-08-15T08:30:00.000Z'
            },
            {
                id: 'LP-2026-000005',
                title: 'Drainase Tersumbat Menyebabkan Genangan Air',
                category: 'lingkungan',
                subcategory: 'Drainase tersumbat',
                description: 'Setiap kali hujan deras air meluap ke pemukiman karena drainase tersumbat sedimen.',
                location: 'Jl. Tubagus Ismail',
                coordinates: { latitude: -6.8870, longitude: 107.6200 },
                date: '2026-08-16',
                time: '16:20',
                urgency: 'tinggi',
                status: 'reported',
                reporter: { id: 'USR-CITIZEN-003', name: 'Siti Aminah' },
                anonymous: false,
                images: [],
                updates: [
                    { status: 'reported', date: '2026-08-16 16:20', note: 'Laporan dibuat.', officer: null }
                ],
                assignedOfficer: null,
                createdAt: '2026-08-16T16:20:00.000Z',
                updatedAt: '2026-08-16T16:20:00.000Z'
            }
        ];

        // Tambahkan dummy tambahan hingga total minimal 20 laporan
        const categories = ['fasilitas', 'pungli', 'sosial', 'lingkungan'];
        const statuses = ['reported', 'verified', 'forwarded', 'processing', 'completed', 'closed'];
        const urgencies = ['rendah', 'sedang', 'tinggi', 'darurat'];

        for (let i = 6; i <= 20; i++) {
            const cat = categories[i % categories.length];
            const subCat = REPORT_CATEGORIES[cat].subcategories[0];
            const stat = statuses[i % statuses.length];
            const urg = urgencies[i % urgencies.length];
            const seqStr = String(i).padStart(6, '0');

            dummyReports.push({
                id: `LP-2026-${seqStr}`,
                title: `Laporan Simulasi Fasilitas dan Publik No ${i}`,
                category: cat,
                subcategory: subCat,
                description: `Ini adalah deskripsi pengujian simulasi sistem civic-tech untuk laporan ke-${i}.`,
                location: `Kecamatan Coblong Wilayah ${i}`,
                coordinates: { latitude: -6.8800 - (i * 0.001), longitude: 107.6100 + (i * 0.001) },
                date: '2026-08-18',
                time: '10:00',
                urgency: urg,
                status: stat,
                reporter: i % 2 === 0 ? MOCK_USERS.CITIZEN : { id: `USR-CITIZEN-00${i}`, name: `Warga ${i}` },
                anonymous: i % 3 === 0,
                images: [],
                updates: [
                    { status: 'reported', date: '2026-08-18 10:00', note: 'Laporan telah dibuat.', officer: null }
                ],
                assignedOfficer: stat !== 'reported' ? 'Petugas Wilayah' : null,
                createdAt: `2026-08-18T10:00:00.0${i}Z`,
                updatedAt: `2026-08-18T10:00:00.0${i}Z`
            });
        }

        setStorage(STORAGE_KEYS.REPORTS, dummyReports);
        setStorage(STORAGE_KEYS.USERS, [MOCK_USERS.CITIZEN, MOCK_USERS.OFFICER]);
    }

    // =========================================================
    // 05. AUTHENTICATION & USER SESSION MANAGEMENT
    // =========================================================
    function getCurrentUser() {
        return getStorage(STORAGE_KEYS.SESSION, null);
    }

    function isLoggedIn() {
        return getCurrentUser() !== null;
    }

    function loginUser(role) {
        const user = role === 'officer' ? MOCK_USERS.OFFICER : MOCK_USERS.CITIZEN;
        setStorage(STORAGE_KEYS.SESSION, user);
        state.currentUser = user;
        updateAuthUI();
        renderDashboard();
    }

    function logoutUser() {
        removeStorage(STORAGE_KEYS.SESSION);
        state.currentUser = null;
        updateAuthUI();
        renderDashboard();
    }

    function updateAuthUI() {
        const headerAccount = document.querySelector('.header-account');
        if (!headerAccount) return;

        const user = getCurrentUser();
        if (user) {
            headerAccount.innerHTML = `
                <span class="staff-identity" style="margin-right: 8px;">${user.name} (${user.role})</span>
                <button type="button" id="btn-logout" class="hero-actions">Keluar</button>
            `;
            const btnLogout = document.getElementById('btn-logout');
            if (btnLogout) {
                btnLogout.addEventListener('click', (e) => {
                    e.preventDefault();
                    logoutUser();
                });
            }
        } else {
            headerAccount.innerHTML = `<a href="#akun-masyarakat">Masuk / Akun</a>`;
        }
    }

    // =========================================================
    // 06. NOTIFICATIONS SYSTEM
    // =========================================================
    function createNotification(userId, message) {
        const notifications = getStorage(STORAGE_KEYS.NOTIFICATIONS, []);
        const newNotif = {
            id: 'NTF-' + Date.now() + '-' + Math.floor(Math.random() * 1000),
            userId: userId,
            message: message,
            date: new Date().toISOString(),
            read: false
        };
        notifications.unshift(newNotif);
        setStorage(STORAGE_KEYS.NOTIFICATIONS, notifications);
        renderNotifications();
    }

    function markNotificationAsRead(notifId) {
        const notifications = getStorage(STORAGE_KEYS.NOTIFICATIONS, []);
        const target = notifications.find(n => n.id === notifId);
        if (target) {
            target.read = true;
            setStorage(STORAGE_KEYS.NOTIFICATIONS, notifications);
            renderNotifications();
        }
    }

    function markAllNotificationsAsRead() {
        const user = getCurrentUser();
        if (!user) return;
        const notifications = getStorage(STORAGE_KEYS.NOTIFICATIONS, []);
        notifications.forEach(n => {
            if (n.userId === user.id) n.read = true;
        });
        setStorage(STORAGE_KEYS.NOTIFICATIONS, notifications);
        renderNotifications();
    }

    function renderNotifications() {
        const user = getCurrentUser();
        const container = document.querySelector('.notification-panel, #notification-list');
        if (!container || !user) return;

        const notifications = getStorage(STORAGE_KEYS.NOTIFICATIONS, []).filter(n => n.userId === user.id);
        const unreadCount = notifications.filter(n => !n.read).length;

        const badge = document.querySelector('.notification-badge');
        if (badge) badge.textContent = unreadCount;

        container.innerHTML = notifications.length === 0 
            ? '<p class="caption">Tidak ada notifikasi.</p>' 
            : notifications.map(n => `
                <div class="notification-item ${n.read ? 'read' : 'unread'}" data-id="${n.id}">
                    <p style="font-size: 0.85rem; margin: 0;">${n.message}</p>
                    <small class="caption">${formatDate(n.date)}</small>
                </div>
            `).join('');
    }

    // =========================================================
    // 07. FORM HANDLING & VALIDATION
    // =========================================================
    function initFormHandling() {
        const categorySelect = document.getElementById('report-category');
        const subcategorySelect = document.getElementById('report-subcategory');
        const form = document.querySelector('#formulir-laporan form');

        if (categorySelect && subcategorySelect) {
            categorySelect.addEventListener('change', (e) => {
                const cat = e.target.value;
                subcategorySelect.innerHTML = '<option value="">Pilih subkategori</option>';
                if (cat && REPORT_CATEGORIES[cat]) {
                    REPORT_CATEGORIES[cat].subcategories.forEach(sub => {
                        const opt = document.createElement('option');
                        opt.value = sub;
                        opt.textContent = sub;
                        subcategorySelect.appendChild(opt);
                    });
                }
            });
        }

        if (form) {
            form.addEventListener('submit', handleReportSubmission);
        }
    }

    function handleReportSubmission(e) {
        e.preventDefault();
        const form = e.target;
        
        // Reset Error Styling
        form.querySelectorAll('.error-message').forEach(el => el.remove());

        const category = form.querySelector('#report-category')?.value.trim();
        const subcategory = form.querySelector('#report-subcategory')?.value.trim();
        const title = form.querySelector('#report-title')?.value.trim();
        const description = form.querySelector('#report-description')?.value.trim();
        const urgency = form.querySelector('#report-urgency')?.value.trim();
        const locationName = form.querySelector('#location-name')?.value.trim();
        const incidentDate = form.querySelector('#incident-date')?.value.trim();
        const isAnonymous = form.querySelector('#identity-hidden')?.checked || false;

        let isValid = true;

        const validateField = (element, condition, msg) => {
            if (!condition) {
         
