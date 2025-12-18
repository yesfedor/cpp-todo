import { createApp } from 'vue'
import { loadModule } from 'vue3-sfc-loader'

const options = {
  moduleCache: {
    vue: await import('vue'),
  },
  async getFile(url) {
    const res = await fetch(url);
    if (!res.ok) throw Object.assign(new Error(res.statusText), { res });
    return {
      getContentData: (asBinary) => asBinary ? res.arrayBuffer() : res.text(),
    }
  },
  addStyle(textContent) {
    const style = document.createElement('style')
    style.textContent = textContent;
    const ref = document.head.getElementsByTagName('style')[0] || null
    document.head.insertBefore(style, ref)
  },
};

const app = createApp(
  await loadModule('/frontend/components/App.vue', options)
);

app.mount('#app')

window.__app__ = app
