:root {
    --color-primary: #16794a;
    --color-primary-dark: #0f5d39;
    --color-primary-light: #e8f5ee;

    --color-background: #f4f7f5;
    --color-surface: #ffffff;
    --color-surface-soft: #f8faf9;

    --color-text: #17221c;
    --color-text-secondary: #46534c;
    --color-text-muted: #718078;

    --color-border: #d9e2dc;
    --color-border-strong: #bdcbc2;

    --color-success: #16804b;
    --color-success-bg: #e7f6ed;

    --color-warning: #a56a00;
    --color-warning-bg: #fff5d9;

    --color-info: #1769aa;
    --color-info-bg: #e8f2fb;

    --color-danger: #b43a3a;
    --color-danger-bg: #fbeaea;

    --color-closed: #69736e;
    --color-closed-bg: #edf0ee;

    --color-white: #ffffff;

    --shadow-sm: 0 1px 3px rgba(20, 38, 29, 0.06);
    --shadow-md: 0 5px 18px rgba(20, 38, 29, 0.08);
    --shadow-lg: 0 12px 30px rgba(20, 38, 29, 0.10);

    --radius-sm: 6px;
    --radius-md: 10px;
    --radius-lg: 16px;
    --radius-xl: 22px;

    --container-width: 1240px;

    --space-1: 0.25rem;
    --space-2: 0.5rem;
    --space-3: 0.75rem;
    --space-4: 1rem;
    --space-5: 1.25rem;
    --space-6: 1.5rem;
    --space-8: 2rem;
    --space-10: 2.5rem;
    --space-12: 3rem;
    --space-16: 4rem;
    --space-20: 5rem;
}


/* =========================================================
   RESET
   ========================================================= */

*,
*::before,
*::after {
    box-sizing: border-box;
}

html {
    font-size: 16px;
    scroll-behavior: smooth;
}

body,
h1,
h2,
h3,
h4,
h5,
h6,
p,
figure,
dl,
dd,
ul,
ol {
    margin: 0;
}

ul,
ol {
    margin: 0;
    padding: 0;
}

button,
input,
select,
textarea {
    font: inherit;
}

button {
    cursor: pointer;
}

img,
svg,
video {
    display: block;
    max-width: 100%;
}

img {
    height: auto;
}

a {
    color: inherit;
}


/* =========================================================
   BASE
   ========================================================= */

body {
    min-width: 320px;
    background: var(--color-background);
    color: var(--color-text);
    font-family:
        Inter,
        ui-sans-serif,
        system-ui,
        -apple-system,
        BlinkMacSystemFont,
        "Segoe UI",
        sans-serif;
    font-size: 1rem;
    line-height: 1.6;
    -webkit-font-smoothing: antialiased;
}

main {
    display: block;
}

a {
    color: var(--color-primary-dark);
    text-decoration-thickness: 1px;
    text-underline-offset: 3px;
}

a:hover {
    color: var(--color-primary);
}

a:focus-visible,
button:focus-visible,
input:focus-visible,
select:focus-visible,
textarea:focus-visible {
    outline: 3px solid rgba(22, 121, 74, 0.25);
    outline-offset: 2px;
}


/* =========================================================
   TYPOGRAPHY
   ========================================================= */

h1,
h2,
h3,
h4 {
    color: var(--color-text);
    font-weight: 700;
    line-height: 1.2;
}

h1 {
    font-size: clamp(2rem, 5vw, 3.6rem);
    letter-spacing: -0.035em;
}

h2 {
    font-size: clamp(1.5rem, 3vw, 2.2rem);
    letter-spacing: -0.025em;
}

h3 {
    font-size: 1.15rem;
}

p {
    color: var(--color-text-secondary);
}

.platform-label {
    margin-bottom: var(--space-3);
    color: var(--color-primary-dark);
    font-size: 0.82rem;
    font-weight: 700;
    letter-spacing: 0.08em;
    text-transform: uppercase;
}


/* =========================================================
   GLOBAL LAYOUT
   ========================================================= */

#main-content {
    width: min(100%, var(--container-width));
    margin-inline: auto;
    padding: 0 var(--space-4) var(--space-16);
}

.page {
    width: 100%;
}

.page > section,
.page > header {
    width: 100%;
}

.page > section {
    margin-top: var(--space-12);
}


/* =========================================================
   HEADER
   ========================================================= */

#site-header {
    position: relative;
    z-index: 10;

    display: flex;
    align-items: center;
    gap: var(--space-6);

    min-height: 72px;
    padding: var(--space-3) max(
        var(--space-4),
        calc((100vw - var(--container-width)) / 2)
    );

    background: var(--color-surface);
    border-bottom: 1px solid var(--color-border);
    box-shadow: var(--shadow-sm);
}

.brand {
    flex: 0 0 auto;
}

.brand a {
    display: inline-flex;
    align-items: center;
    gap: var(--space-3);

    color: var(--color-text);
    font-size: 1.2rem;
    font-weight: 800;
    letter-spacing: -0.02em;
    text-decoration: none;
}

.logo-placeholder {
    display: inline-grid;
    place-items: center;

    width: 38px;
    height: 38px;

    border: 1px solid var(--color-border-strong);
    border-radius: var(--radius-md);

    color: var(--color-primary-dark);
    font-size: 0.65rem;
    font-weight: 700;
}

#site-header nav {
    flex: 1;
}

#site-header nav ul {
    display: flex;
    align-items: center;
    justify-content: center;
    gap: var(--space-2);
    list-style: none;
}

#site-header nav a,
.header-account a {
    display: inline-flex;
    align-items: center;

    min-height: 40px;
    padding: 0.45rem 0.8rem;

    border-radius: var(--radius-sm);

    color: var(--color-text-secondary);
    font-size: 0.92rem;
    font-weight: 600;
    text-decoration: none;
}

#site-header nav a:hover,
.header-account a:hover {
    background: var(--color-primary-light);
    color: var(--color-primary-dark);
}

.header-account {
    flex: 0 0 auto;
}

.header-account a {
    border: 1px solid var(--color-border);
    background: var(--color-surface);
    color: var(--color-primary-dark);
}


/* =========================================================
   NAVIGATION
   ========================================================= */

.page-report-form > nav {
    margin-bottom: var(--space-8);
}

.page-report-form > nav ol {
    display: flex;
    flex-wrap: wrap;
    align-items: center;
    gap: 0.35rem;

    color: var(--color-text-muted);
    font-size: 0.875rem;
    list-style: none;
}

.page-report-form > nav li + li::before {
    content: "/";
    margin-right: 0.35rem;
    color: var(--color-border-strong);
}


/* =========================================================
   HERO
   ========================================================= */

.page-public > .page-header {
    max-width: 850px;
    margin-inline: auto;
    padding: clamp(4rem, 9vw, 7rem) var(--space-4)
        clamp(3rem, 7vw, 5rem);

    text-align: center;
}

.page-header h1 {
    max-width: 800px;
    margin-inline: auto;
}

.page-header > p:not(.platform-label) {
    max-width: 680px;
    margin: var(--space-5) auto 0;
    font-size: clamp(1rem, 2vw, 1.15rem);
}

.hero-actions {
    display: flex;
    flex-wrap: wrap;
    justify-content: center;
    gap: var(--space-3);
    margin-top: var(--space-8);
}

.hero-actions a {
    display: inline-flex;
    align-items: center;
    justify-content: center;

    min-height: 46px;
    padding: 0.7rem 1.25rem;

    border: 1px solid var(--color-primary);
    border-radius: var(--radius-md);

    background: var(--color-primary);
    color: var(--color-white);

    font-weight: 700;
    text-decoration: none;
}

.hero-actions a:hover {
    background: var(--color-primary-dark);
    border-color: var(--color-primary-dark);
}

.hero-actions a + a {
    background: var(--color-surface);
    color: var(--color-primary-dark);
}


/* =========================================================
   SEARCH
   ========================================================= */

#search-section {
    padding: clamp(1.25rem, 3vw, 2rem);

    background: var(--color-surface);
    border: 1px solid var(--color-border);
    border-radius: var(--radius-lg);
    box-shadow: var(--shadow-sm);
}

#search-section header {
    margin-bottom: var(--space-4);
}

#search-section h2 {
    font-size: 1.35rem;
}

#search-section form {
    display: grid;
    grid-template-columns: 1fr auto;
    gap: var(--space-3);
}

#global-search {
    width: 100%;
    min-height: 48px;
    padding: 0.7rem 0.9rem;

    border: 1px solid var(--color-border-strong);
    border-radius: var(--radius-md);

    background: var(--color-surface);
    color: var(--color-text);
}

#global-search::placeholder {
    color: var(--color-text-muted);
}

#global-search:focus {
    border-color: var(--color-primary);
    outline: none;
}

#search-section button {
    min-height: 48px;
    padding: 0.7rem 1.25rem;

    border: 1px solid var(--color-primary);
    border-radius: var(--radius-md);

    background: var(--color-primary);
    color: var(--color-white);
    font-weight: 700;
}

#search-section button:hover {
    background: var(--color-primary-dark);
}


/* =========================================================
   CATEGORY CARDS
   ========================================================= */

#kategori-laporan > header {
    margin-bottom: var(--space-6);
}

#kategori-laporan > header p {
    margin-top: var(--space-2);
}

.report-category-list {
    display: grid;
    grid-template-columns: repeat(4, minmax(0, 1fr));
    gap: var(--space-4);
}

.report-category {
    display: flex;
    flex-direction: column;

    min-width: 0;
    padding: var(--space-5);

    background: var(--color-surface);
    border: 1px solid var(--color-border);
    border-radius: var(--radius-lg);
    box-shadow: var(--shadow-sm);
}

.report-category:hover {
    border-color: var(--color-border-strong);
    box-shadow: var(--shadow-md);
}

.report-category header {
    margin-bottom: var(--space-4);
}

.report-category ul {
    display: grid;
    gap: 0.55rem;

    padding-left: 1.1rem;
    color: var(--color-text-secondary);
}

.report-category li {
    padding-left: 0.15rem;
    font-size: 0.9rem;
}

.report-category aside {
    margin-top: var(--space-4);
    padding: var(--space-3);

    background: var(--color-primary-light);
    border-left: 3px solid var(--color-primary);
    border-radius: var(--radius-sm);
}

.report-category aside p {
    font-size: 0.82rem;
}

.report-category footer {
    margin-top: auto;
    padding-top: var(--space-5);
}

.report-category footer a {
    display: inline-flex;
    align-items: center;

    min-height: 40px;

    color: var(--color-primary-dark);
    font-size: 0.9rem;
    font-weight: 700;
}


/* =========================================================
   STATISTICS
   ========================================================= */

#kondisi-wilayah > header {
    margin-bottom: var(--space-6);
}

.statistics-summary {
    display: grid;
    grid-template-columns: repeat(4, minmax(0, 1fr));
    gap: var(--space-4);
}

.statistics-summary article {
    padding: var(--space-5);

    background: var(--color-surface);
    border: 1px solid var(--color-border);
    border-radius: var(--radius-lg);
}

.statistics-summary h3 {
    margin-bottom: var(--space-3);

    color: var(--color-text-muted);
    font-size: 0.86rem;
    font-weight: 600;
}

.statistics-summary data {
    display: block;

    color: var(--color-text);
    font-size: clamp(1.8rem, 4vw, 2.5rem);
    font-weight: 800;
    line-height: 1;
}

.statistics-visualization {
    display: grid;
    grid-template-columns: repeat(3, minmax(0, 1fr));
    gap: var(--space-4);
    margin-top: var(--space-4);
}

.statistics-visualization figure {
    min-width: 0;
    overflow: hidden;

    background: var(--color-surface);
    border: 1px solid var(--color-border);
    border-radius: var(--radius-lg);
}

.statistics-visualization figcaption {
    padding: var(--space-4);

    border-bottom: 1px solid var(--color-border);

    color: var(--color-text);
    font-size: 0.9rem;
    font-weight: 700;
}

.chart-placeholder {
    display: grid;
    place-items: center;

    min-height: 230px;
    padding: var(--space-4);

    background: var(--color-surface-soft);
    color: var(--color-text-muted);

    text-align: center;
    font-size: 0.82rem;
}


/* =========================================================
   REPORT CARDS
   ========================================================= */

.latest-report-list {
    display: grid;
    grid-template-columns: repeat(2, minmax(0, 1fr));
    gap: var(--space-5);
}

.report-card {
    min-width: 0;
    padding: var(--space-5);

    background: var(--color-surface);
    border: 1px solid var(--color-border);
    border-radius: var(--radius-lg);
    box-shadow: var(--shadow-sm);
}

.report-card > header {
    margin-bottom: var(--space-4);
}

.report-card > header p {
    margin-bottom: var(--space-2);
    color: var(--color-text-muted);
    font-size: 0.8rem;
}

.report-card h3 {
    font-size: 1.2rem;
}

.report-card dl {
    display: grid;
    grid-template-columns: 90px 1fr;
    gap: 0.45rem 1rem;

    padding: var(--space-4) 0;

    border-top: 1px solid var(--color-border);
    border-bottom: 1px solid var(--color-border);
}

.report-card dt {
    color: var(--color-text-muted);
    font-size: 0.82rem;
    font-weight: 600;
}

.report-card dd {
    min-width: 0;
    color: var(--color-text-secondary);
    font-size: 0.88rem;
}

.report-card > p {
    margin: var(--space-4) 0;
    font-size: 0.92rem;
}

.report-card figure {
    margin-top: var(--space-4);
}

.image-placeholder {
    display: grid;
    place-items: center;

    min-height: 180px;
    padding: var(--space-4);

    overflow: hidden;

    background: var(--color-surface-soft);
    border: 1px dashed var(--color-border-strong);
    border-radius: var(--radius-md);

    color: var(--color-text-muted);
    text-align: center;
    font-size: 0.8rem;
}

.report-card figcaption {
    margin-top: var(--space-2);

    color: var(--color-text-muted);
    font-size: 0.75rem;
}

.report-card > a:last-child {
    display: inline-flex;
    margin-top: var(--space-4);
    font-weight: 700;
}


/* =========================================================
   STATUS BADGES
   ========================================================= */

.status {
    display: inline-flex;
    align-items: center;
    gap: 0.4rem;

    min-height: 28px;
    padding: 0.2rem 0.65rem;

    border: 1px solid transparent;
    border-radius: 999px;

    font-size: 0.75rem;
    font-weight: 700;
    line-height: 1.2;
    white-space: nowrap;
}

.status::before {
    content: "";
    width: 6px;
    height: 6px;
    border-radius: 50%;
    background: currentColor;
}

.status-dilaporkan,
.status-reported {
    background: var(--color-warning-bg);
    border-color: #ead7a4;
    color: var(--color-warning);
}

.status-diverifikasi,
.status-verified {
    background: var(--color-info-bg);
    border-color: #c7dced;
    color: var(--color-info);
}

.status-diteruskan,
.status-forwarded {
    background: var(--color-info-bg);
    border-color: #c7dced;
    color: var(--color-info);
}

.status-dalam-penanganan,
.status-processing {
    background: var(--color-warning-bg);
    border-color: #ead7a4;
    color: var(--color-warning);
}

.status-selesai,
.status-completed {
    background: var(--color-success-bg);
    border-color: #b9ddc8;
    color: var(--color-success);
}

.status-ditutup,
.status-closed {
    background: var(--color-closed-bg);
    border-color: #d3dad6;
    color: var(--color-closed);
}


/* =========================================================
   FORM
   ========================================================= */

.page-report-form {
    max-width: 900px;
    margin-inline: auto;
    padding-top: var(--space-12);
}

.page-report-form > header {
    margin-bottom: var(--space-6);
}

.page-report-form > header p {
    margin-top: var(--space-2);
}

.page-report-form > form {
    display: grid;
    gap: var(--space-5);
}

.page-report-form fieldset {
    min-width: 0;
    margin: 0;
    padding: clamp(1.25rem, 3vw, 2rem);

    background: var(--color-surface);
    border: 1px solid var(--color-border);
    border-radius: var(--radius-lg);
    box-shadow: var(--shadow-sm);
}

.page-report-form legend {
    padding: 0 var(--space-2);

    color: var(--color-text);
    font-size: 1.1rem;
    font-weight: 700;
}

.form-field {
    display: grid;
    gap: 0.45rem;
    margin-top: var(--space-5);
}

.form-field label {
    color: var(--color-text);
    font-size: 0.9rem;
    font-weight: 650;
}

.form-field input:not([type="checkbox"]):not([type="radio"]),
.form-field select,
.form-field textarea {
    width: 100%;
    min-height: 46px;
    padding: 0.7rem 0.8rem;

    border: 1px solid var(--color-border-strong);
    border-radius: var(--radius-md);

    background: var(--color-surface);
    color: var(--color-text);
}

.form-field textarea {
    min-height: 140px;
    resize: vertical;
}

.form-field input[type="file"] {
    width: 100%;
    min-height: 48px;
    padding: 0.6rem;

    border: 1px dashed var(--color-border-strong);
    border-radius: var(--radius-md);

    background: var(--color-surface-soft);
    color: var(--color-text-secondary);
}

.form-field input[type="checkbox"],
.form-field input[type="radio"] {
    width: 18px;
    height: 18px;
    accent-color: var(--color-primary);
}

.form-field input:focus,
.form-field select:focus,
.form-field textarea:focus {
    border-color: var(--color-primary);
    outline: 3px solid rgba(22, 121, 74, 0.12);
}


/* =========================================================
   MAP
   ========================================================= */

.map-placeholder {
    margin-top: var(--space-5);
}

.map-placeholder figcaption {
    margin-bottom: var(--space-2);

    color: var(--color-text);
    font-size: 0.9rem;
    font-weight: 650;
}

.map-placeholder > div {
    display: grid;
    place-items: center;

    min-height: 280px;
    padding: var(--space-5);

    overflow: hidden;

    background: var(--color-surface-soft);
    border: 1px solid var(--color-border);
    border-radius: var(--radius-lg);

    color: var(--color-text-muted);
    text-align: center;
}


/* =========================================================
   BUTTONS
   ========================================================= */

button {
    min-height: 42px;
    padding: 0.55rem 1rem;

    border: 1px solid var(--color-border-strong);
    border-radius: var(--radius-md);

    background: var(--color-surface);
    color: var(--color-text);
}

button:hover {
    border-color: var(--color-primary);
}


/* =========================================================
   TABLE
   ========================================================= */

table {
    width: 100%;
    border-collapse: collapse;
    background: var(--color-surface);
}

th,
td {
    padding: 0.8rem 1rem;
    border-bottom: 1px solid var(--color-border);
    text-align: left;
}

th {
    background: var(--color-surface-soft);
    color: var(--color-text);
    font-size: 0.8rem;
    font-weight: 700;
}

td {
    color: var(--color-text-secondary);
    font-size: 0.9rem;
}

tbody tr:hover {
    background: var(--color-surface-soft);
}


/* =========================================================
   STATES
   ========================================================= */

.image-placeholder,
.chart-placeholder,
.map-placeholder > div {
    user-select: none;
}

[aria-busy="true"] {
    cursor: progress;
}

[aria-disabled="true"],
:disabled {
    opacity: 0.65;
}


/* =========================================================
   TABLET
   ========================================================= */

@media (max-width: 1023px) {
    #site-header {
        gap: var(--space-4);
    }

    #site-header nav ul {
        gap: 0;
    }

    .report-category-list {
        grid-template-columns: repeat(2, minmax(0, 1fr));
    }

    .statistics-summary {
        grid-template-columns: repeat(2, minmax(0, 1fr));
    }

    .statistics-visualization {
        grid-template-columns: 1fr;
    }

    .latest-report-list {
        grid-template-columns: 1fr;
    }
}


/* =========================================================
   MOBILE
   ========================================================= */

@media (max-width: 767px) {
    #site-header {
        display: grid;
        grid-template-columns: 1fr auto;
        gap: var(--space-2);

        padding: var(--space-3) var(--space-4);
    }

    #site-header nav {
        grid-column: 1 / -1;
        grid-row: 2;
        overflow-x: auto;
    }

    #site-header nav ul {
        justify-content: flex-start;
        min-width: max-content;
    }

    #site-header nav a {
        min-height: 38px;
        padding-inline: 0.65rem;
        font-size: 0.82rem;
    }

    .header-account a {
        min-height: 38px;
        font-size: 0.8rem;
    }

    #main-content {
        padding-inline: var(--space-3);
    }

    .page-public > .page-header {
        padding-top: var(--space-12);
        padding-bottom: var(--space-10);
    }

    .page-header h1 {
        font-size: clamp(2rem, 11vw, 2.8rem);
    }

    .hero-actions {
        flex-direction: column;
        align-items: stretch;
    }

    .hero-actions a {
        width: 100%;
    }

    #search-section form {
        grid-template-columns: 1fr;
    }

    #search-section button {
        width: 100%;
    }

    .report-category-list {
        grid-template-columns: 1fr;
    }

    .statistics-summary {
        grid-template-columns: repeat(2, minmax(0, 1fr));
    }

    .statistics-summary article {
        padding: var(--space-4);
    }

    .statistics-visualization {
        grid-template-columns: 1fr;
    }

    .latest-report-list {
        grid-template-columns: 1fr;
    }

    .report-card {
        padding: var(--space-4);
    }

    .report-card dl {
        grid-template-columns: 1fr;
        gap: 0.15rem;
    }

    .report-card dt {
        margin-top: 0.5rem;
    }

    .page-report-form {
        padding-top: var(--space-8);
    }

    .page-report-form fieldset {
        padding: var(--space-4);
    }

    .map-placeholder > div {
        min-height: 220px;
    }
}


/* =========================================================
   SMALL MOBILE
   ========================================================= */

@media (max-width: 420px) {
    #site-header {
        grid-template-columns: 1fr;
    }

    .header-account {
        display: none;
    }

    #site-header nav {
        grid-column: 1;
    }

    .brand a {
        font-size: 1.05rem;
    }

    .logo-placeholder {
        width: 34px;
        height: 34px;
    }

    .statistics-summary {
        grid-template-columns: 1fr;
    }

    .chart-placeholder {
        min-height: 190px;
    }

    .image-placeholder {
        min-height: 150px;
    }
}


/* =========================================================
   LARGE DESKTOP
   ========================================================= */

@media (min-width: 1440px) {
    #main-content {
        padding-inline: var(--space-6);
    }

    #site-header {
        padding-inline: max(
            var(--space-6),
            calc((100vw - var(--container-width)) / 2)
        );
    }
}


/* =========================================================
   ACCESSIBILITY
   ========================================================= */

@media (prefers-reduced-motion: reduce) {
    html {
        scroll-behavior: auto;
    }

    *,
    *::before,
    *::after {
        transition: none !important;
        animation: none !important;
    }
}


/* =========================================================
   PRINT
   ========================================================= */

@media print {
    #site-header {
        box-shadow: none;
    }

    .hero-actions,
    #search-section,
    button {
        display: none;
    }

    body {
        background: #ffffff;
        color: #000000;
    }

    .report-category,
    .report-card,
    .statistics-summary article,
    .statistics-visualization figure,
    .page-report-form fieldset {
        box-shadow: none;
        break-inside: avoid;
    }
}
