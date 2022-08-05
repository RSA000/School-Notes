document.addEventListener('DOMContentLoaded', () => {
    const themeStylesheet = document.getElementById('theme')
    const themeToggle = document.getElementById('theme-toggle')
    themeToggle.addEventListener('click', () => {
      // if it's light -> go dark
      if (themeStylesheet.href.includes('light')) {
        themeStylesheet.href = '/static/css/dark-theme.css'
        themeToggle.innerText = 'Switch to light mode'
      } else {
        // if it's dark -> go light
        themeStylesheet.href = '/static/css/light-theme.css'
        themeToggle.innerText = 'Switch to dark mode'
      }
    })
  })